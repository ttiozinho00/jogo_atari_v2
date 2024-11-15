/*
* conpilar: gcc -o atari_v2 atari_v2.c -Wall -pedantic -Wextra -Werror
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*Constantes */
#define LINHAS 20
#define COLUNAS 40
#define BURACO 8

char arena[LINHAS][COLUNAS];
int tabu_esq, tabu_dir;
int bola_x, bola_y;
int dx, dy;
int vel_tabu = 100, vel_bola = 100;

/*Função para ocultar o cursor*/
void ocultar_cursor() 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/*Função para definir a posição do cursor*/ 
void posicao_cursor(int x, int y) 
{
    COORD coord;
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*Função para alterar a cor do texto*/ 
void cor_texto(int cor) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

/*Função para inicializar a arena*/ 
void inicializar_arena() 
{
	int i;
	int j;

    for (i = 0; i < LINHAS; i++) 
    {
        for (j = 0; j < COLUNAS; j++) 
        {
            if (i == 0 || i == LINHAS - 1 || (j == 0 && (i < 6 || i >= 14)) || (j == COLUNAS - 1 && (i < 6 || i >= 14))) 
            {
                arena[i][j] = ''; /*Paredes e buracos*/ 
            } 

            else 
            {
                arena[i][j] = ' ';
            }
        }
    }
    tabu_esq = 8;
    tabu_dir = 8;
    bola_x = 10;
    bola_y = 20;
    dx = (rand() % 2) * 2 - 1;
    dy = (rand() % 2) * 2 - 1;
}

/*Função para desenhar a arena*/ 
void desenhar_arena() 
{
	int i;
	int j;

    posicao_cursor(0, 0);
    for (i = 0; i < LINHAS; i++) 
    {
        for (j = 0; j < COLUNAS; j++) 
        {
            if (j == 1 && i >= tabu_esq && i < tabu_esq + 3) 
            {
                cor_texto(11); /*Azul claro para a tábua esquerda*/ 
                printf("%c", 179); /*Caractere da tábua (linha vertical)*/ 
            } 

            else if (j == COLUNAS - 2 && i >= tabu_dir && i < tabu_dir + 3) 
            {
                cor_texto(14); /*Amarelo para a tábua direita*/ 
                printf("%c", 179);
            } 

            else if (i == bola_x && j == bola_y) 
            {
                cor_texto(12); /*Vermelho para a bola*/ 
                printf("O");
            } 

            else 
            {
                cor_texto(7); /*Branco para o restante*/ 
                printf("%c", arena[i][j]);
            }
        }
        printf("\n");
    }
}

/*Função para mover as tábuas*/ 
void movimento_tabuas() 
{
    if (GetAsyncKeyState('A') & 0x8000 && tabu_esq > 1) 
    {
        tabu_esq--;
    } 

    else if (GetAsyncKeyState('Z') & 0x8000 && tabu_esq < LINHAS - 4) 
    {
        tabu_esq++;
    }

    if (GetAsyncKeyState(VK_UP) & 0x8000 && tabu_dir > 1) 
    {
        tabu_dir--;
    } 

    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && tabu_dir < LINHAS - 4) 
    {
        tabu_dir++;
    }
}

/*Função para mover a bola*/ 
void movimento_bola() 
{
    bola_x += dx;
    bola_y += dy;

    if (bola_x <= 0 || bola_x >= LINHAS - 1) 
    {
        dx = -dx;
        Beep(1000, 100); /*Som ao bater na borda*/ 
    }

    if (bola_y == 1 && bola_x >= tabu_esq && bola_x < tabu_esq + 3) 
    {
        dy = -dy;
        Beep(800, 100); /*Som ao bater na tábua esquerda*/ 
    } 

    else if (bola_y == COLUNAS - 2 && bola_x >= tabu_dir && bola_x < tabu_dir + 3) 
    {
        dy = -dy;
        Beep(800, 100); /*Som ao bater na tábua direita*/ 
    }

    if (bola_y <= 0 || bola_y >= COLUNAS - 1) 
    {
        cor_texto(12);
        printf("Fim de jogo!\n");
        printf("O jogador %s perdeu!\n", bola_y <= 0 ? "da esquerda" : "da direita");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    argv = argv;
    argc = argc;
    
	srand(time(NULL));
    ocultar_cursor();
    inicializar_arena();

    while (1) 
    {
        desenhar_arena();
        movimento_tabuas();
        movimento_bola();
        Sleep(vel_bola);
    }

	return 0;
}
