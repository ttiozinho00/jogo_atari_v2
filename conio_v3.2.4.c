/*conio_v3.2.4.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <string.h>
#include <stdarg.h>
#include "conio_v3.2.4.h"

#ifdef __cplusplus
extern "C" {
#endif

text_info vActual = {0, 0, 249, 79, WHITE, WHITE, C80, 80, 250, 1, 1};

char *cgets(char *str)
{
   DWORD longitud = 0;
   DWORD leidos, modo;

   GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &modo);
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT);
   do {
      ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &str[2+longitud], 1,&leidos, NULL);
      if(str[2+longitud] != '\r') putch(str[2+longitud++]);
   } while(longitud < (unsigned char) str[0] && str[2+longitud] != '\r');
   str[1] = longitud;
   str[2+longitud] = 0;
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo);
   return &str[2];
}

void clreol ()
{
   COORD coord;
   DWORD escrito;

   coord.X = vActual.winleft+vActual.curx-1;
   coord.Y = vActual.wintop+vActual.cury-1;

   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',vActual.screenwidth - vActual.curx + 1, coord, &escrito);
   FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),vActual.attribute, vActual.screenwidth - vActual.curx + 1,coord, &escrito);
   gotoxy(vActual.curx, vActual.cury);
}

void clrscr ()
{
   DWORD escrito;
   COORD coord;
   int i;

   for( i = 0; i < vActual.screenheight; i++) {
      coord.X = vActual.winleft;
      coord.Y = vActual.wintop+i;
      FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),vActual.attribute, vActual.screenwidth, coord, &escrito);
      FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',vActual.screenwidth, coord, &escrito);
   }
   gotoxy(vActual.curx, vActual.cury);
}

int cprintf(const char *format, ...)
{
  /* char *buffer;		this is not "c" (this is c++).*/
  char buffer[1024] = { 0 };
  va_list p;
  int n;
  va_start(p, format);
  n = vsprintf(buffer, format, p);
  cputs(buffer);
  return n;
}

int cputs(const char *str) /* repasar */
{
   DWORD escritos;
   int n = 0;
   unsigned int resto = vActual.screenwidth-vActual.curx+1;

   do {
      if(strlen(&str[n]) < resto) resto = strlen(&str[n]);
      gotoxy(vActual.curx, vActual.cury);
      WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), &str[n], resto, &escritos,NULL);
      n+=resto;
      vActual.curx+=resto;
      if(vActual.curx > vActual.screenwidth) {
         vActual.curx -= vActual.screenwidth;
         resto = vActual.screenwidth-vActual.curx+1;
         vActual.cury++;
         resto = vActual.screenwidth;
         if(vActual.cury > vActual.screenheight) {
            vActual.cury--;
            movetext(1, 2, vActual.screenwidth, vActual.screenheight, 1, 1);
         }
      }
   } while(str[n]);
   return strlen(str);
}

void delline()
{
   COORD coord;
   SMALL_RECT origen;
   SMALL_RECT clip;
   CHAR_INFO ci;

   origen.Left = vActual.winleft;
   origen.Top = vActual.wintop+vActual.cury;
   origen.Right = vActual.winright;
   origen.Bottom = vActual.winbottom;
   coord.X = vActual.winleft;
   coord.Y = vActual.wintop+vActual.cury-1;
   clip.Left = vActual.winleft;
   clip.Top = vActual.wintop;
   clip.Right = vActual.winright;
   clip.Bottom = vActual.winbottom;
   ci.Char.AsciiChar = ' ';
   ci.Attributes = vActual.attribute;
   ScrollConsoleScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE),&origen, &clip, coord, &ci);
   vActual.curx = 1;
   gotoxy(vActual.curx, vActual.cury);
}

int getch(void)
{
   HANDLE hStdin;
   static INPUT_RECORD irInBuf;
   DWORD cNumRead;
   static int vez = 1;
   int codigo;

   hStdin = GetStdHandle(STD_INPUT_HANDLE);

   /* eliminar do buffer de entrada todas os eventos de liberação de tecla */
   do{
      if (vez == 1) ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
	 }while(irInBuf.Event.KeyEvent.bKeyDown == FALSE);

   if(irInBuf.EventType == KEY_EVENT) /* identificar alguma entrada do teclado */
   {
      if(irInBuf.Event.KeyEvent.bKeyDown == TRUE) /* identificar se foi pressionada alguma tecla */
      {
 	     if(vez == 1) /* se for uma tecla comum, o código retornado será diferente de 0 */
            codigo = irInBuf.Event.KeyEvent.uChar.AsciiChar;
		 else /* se for uma tecla especial. Por exemplo: F1 */
		 {
            codigo = irInBuf.Event.KeyEvent.wVirtualScanCode; /* armazenar o código da tecla especial */
			vez = 1;
	     }
			if (codigo == 0)
			    vez = 2;
	     }
      }

   return codigo;
}

int getche(void)
{
   HANDLE hStdin;
   static INPUT_RECORD irInBuf;
   DWORD cNumRead;
   static int vez = 1;
   int codigo;

   hStdin = GetStdHandle(STD_INPUT_HANDLE);

   /* eliminar do buffer de entrada todas os eventos de liberação de tecla */
   do{
      if (vez == 1) ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead);
	 }while(irInBuf.Event.KeyEvent.bKeyDown == FALSE);

   if(irInBuf.EventType == KEY_EVENT) /* identificar alguma entrada do teclado */
   {
      if(irInBuf.Event.KeyEvent.bKeyDown == TRUE) /* identificar se foi pressionada alguma tecla */
      {
 	     if(vez == 1) /* se for uma tecla comum, o código retornado será diferente de 0 */
            codigo = irInBuf.Event.KeyEvent.uChar.AsciiChar;
		 else /* se for uma tecla especial. Por exemplo: F1 */
		 {
            codigo = irInBuf.Event.KeyEvent.wVirtualScanCode; /* armazenar o código da tecla especial */
			vez = 1;
	     }
			if (codigo == 0)
			    vez = 2;
	  }
   }
   putchar(codigo);

   return codigo;

}

char *getpass(const char *prompt)
{
   static char pass[9];
   DWORD longitud = 0;
   DWORD leidos, modo;

   cputs(prompt);
   GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &modo);
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT);
   do {
      ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &pass[longitud], 1, &leidos,NULL);
      if(pass[longitud] != '\r') longitud++;
   } while(longitud < 8 && pass[longitud] != '\r');
   pass[longitud] = 0;
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo);
   return pass;
}

int _gettext(int left, int top, int right, int bottom, void *destin)
{
   PCHAR_INFO buffer;
   char *pantalla = (char *)destin;
   int retval,i;

   COORD cSize;
   COORD cDest = {0,0};
   SMALL_RECT rect;

   rect.Left = vActual.winleft+left-1;
   rect.Top = vActual.wintop+top-1;
   rect.Right = vActual.winleft+right-1;
   rect.Bottom = vActual.wintop+bottom-1;

   cSize.X = 1 + right - left;
   cSize.Y = 1 + bottom - top;
   buffer = (PCHAR_INFO)malloc(cSize.X*cSize.Y*sizeof(CHAR_INFO));

   retval = ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),
      buffer, cSize, cDest, &rect);
   for( i = 0; i < cSize.X * cSize.Y; i++) {
      pantalla[2*i] = buffer[i].Char.AsciiChar;
      pantalla[2*i + 1] = buffer[i].Attributes & 0xff;
   }

   free( buffer );
   return retval;
}

void gettextinfo(struct text_info *r)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

   *r = vActual;
}

void gotoxy(int x, int y)
{
   COORD c;

   if(x < 1 || x > vActual.screenwidth || y < 1 || y > vActual.screenheight) return;
   vActual.curx = x;
   vActual.cury = y;
   c.X = vActual.winleft + x - 1;
   c.Y = vActual.wintop + y - 1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void highvideo(void)
{
   vActual.attribute |= FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vActual.attribute);
}

void insline(void)
{
   COORD coord;
   SMALL_RECT origen;
   SMALL_RECT clip;
   CHAR_INFO ci;

   origen.Left = vActual.winleft;
   origen.Top = vActual.wintop+vActual.cury-1;
   origen.Right = vActual.winright;
   origen.Bottom = vActual.winbottom;
   coord.X = vActual.winleft;
   coord.Y = vActual.wintop+vActual.cury;
   clip.Left = vActual.winleft;
   clip.Top = vActual.wintop;
   clip.Right = vActual.winright;
   clip.Bottom = vActual.winbottom;
   ci.Char.AsciiChar = ' ';
   ci.Attributes = vActual.attribute;
   ScrollConsoleScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE),&origen, &clip, coord, &ci);
   vActual.curx = 1;
   gotoxy(vActual.curx, vActual.cury);
}

int kbhit(void)
{
   DWORD nEventos;
   INPUT_RECORD *eventos;
   DWORD leidos;
   int retval = 0;
   unsigned int i;

   GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE),&nEventos);
   /* eventos = new INPUT_RECORD[nEventos]; */
   eventos = (INPUT_RECORD *)malloc(nEventos*sizeof(INPUT_RECORD));
   PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE),eventos, nEventos, &leidos);

   for(i = 0;  i < nEventos; i++)
      if(eventos[i].EventType == KEY_EVENT && eventos[i].Event.KeyEvent.bKeyDown) retval = 1;
   free( eventos );
   return retval;
}

void lowvideo(void)
{
   vActual.attribute &= ~FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vActual.attribute);
}

int movetext(int left, int top, int right, int bottom, int destleft,int desttop)
{
   COORD coord;
   SMALL_RECT origen;
   CHAR_INFO ci;

   origen.Left   = vActual.winleft+left-1;
   origen.Top    = vActual.wintop+top-1;
   origen.Right  = vActual.winleft+right-1;
   origen.Bottom = vActual.wintop+bottom-1;
   coord.X       = vActual.winleft+destleft-1;
   coord.Y       = vActual.wintop+desttop-1;
   ci.Char.AsciiChar = ' ';
   ci.Attributes = vActual.attribute;
   ScrollConsoleScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE),&origen, NULL, coord, &ci);
   return 0;
}

void normvideo(void)
{
   vActual.attribute = vActual.normattr;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vActual.attribute);
}

int putch(int c)
{
   DWORD escritos;

   gotoxy(vActual.curx, vActual.cury);
   WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), (char*)&c, 1, &escritos,NULL);
   vActual.curx++;
   if(vActual.curx > vActual.screenwidth) {
      vActual.curx -= vActual.screenwidth;
      vActual.cury++;
      if(vActual.cury > vActual.screenheight) {
         vActual.cury--;
         movetext(1, 2, vActual.screenwidth, vActual.screenheight, 1, 1);
      }
   }
   return 0;
}

int puttext(int left, int top, int right, int bottom, void *source)
{
   PCHAR_INFO buffer;
   char *pantalla = (char *)source;
   int retval,i;

   COORD cSize;
   COORD cDest = {0,0};
   SMALL_RECT rect;

   rect.Left = vActual.winleft+left-1;
   rect.Top = vActual.wintop+top-1;
   rect.Right = vActual.winleft+right-1;
   rect.Bottom = vActual.wintop+bottom-1;

   cSize.X = 1 + right - left;
   cSize.Y = 1 + bottom - top;
   buffer = (PCHAR_INFO)malloc(sizeof(CHAR_INFO)*cSize.X * cSize.Y);

   for( i = 0; i < cSize.X * cSize.Y; i++) {
      buffer[i].Char.AsciiChar = pantalla[2*i];
      buffer[i].Attributes = (WORD)pantalla[2*i + 1];
   }

   retval = WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),buffer, cSize, cDest, &rect);
   free(buffer);
   return retval;
}

void _setcursortype(int cur_t)
{
   CONSOLE_CURSOR_INFO cci;

   switch(cur_t) {
      case _NOCURSOR:
         cci.dwSize = 100;
         cci.bVisible = FALSE;
         break;
      case _SOLIDCURSOR:
         cci.dwSize = 100;
         cci.bVisible = TRUE;
         break;
      case _NORMALCURSOR:
         cci.dwSize = 10;
         cci.bVisible = TRUE;
         break;
   }
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void textattr(int newattr)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newattr);
   vActual.attribute = newattr;
}


void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

/* Puts screen in text mode. */
void textmode(int newmode)
{
	/* Silence the "unused-parameter" warning. */
	newmode = newmode;
}

int ungetch(int ch)
{
   INPUT_RECORD ir[2];
   DWORD escritos;

   ir[0].EventType = KEY_EVENT;
   ir[0].Event.KeyEvent.bKeyDown = TRUE;
   ir[0].Event.KeyEvent.wRepeatCount = 1;
   ir[0].Event.KeyEvent.wVirtualKeyCode = 0;
   ir[0].Event.KeyEvent.wVirtualScanCode = 0;
   ir[0].Event.KeyEvent.uChar.AsciiChar = ch;
   ir[0].Event.KeyEvent.dwControlKeyState = 0;
   ir[1].EventType = KEY_EVENT;
   ir[1].Event.KeyEvent.bKeyDown = FALSE;
   ir[1].Event.KeyEvent.wRepeatCount = 1;
   ir[1].Event.KeyEvent.wVirtualKeyCode = 0;
   ir[1].Event.KeyEvent.wVirtualScanCode = 0;
   ir[1].Event.KeyEvent.uChar.AsciiChar = ch;
   ir[1].Event.KeyEvent.dwControlKeyState = 0;
   if(WriteConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ir, 2, &escritos)) return ch;
   return EOF;
}

int wherex(void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
return info.dwCursorPosition.X + 1;
}

int wherey(void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
return info.dwCursorPosition.Y + 1;
}

void window(int left, int top, int right, int bottom)
{
   vActual.winleft   = left-1;
   vActual.wintop    = top-1;
   vActual.winright  = right-1;
   vActual.winbottom = bottom-1;
   vActual.screenheight = 1+bottom-top;
   vActual.screenwidth  = 1+right-left;
   vActual.curx = 1;
   vActual.cury = 1;
   clrscr();
}

#ifdef __cplusplus
}
#endif