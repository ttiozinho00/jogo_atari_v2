#include <stdio.h>       /* printf(), putch() */
#include <stdlib.h>      /* exit() */
#include <time.h>        /* time(), rand() */
#include <windows.h>     /* Beep(), Sleep() */

#include "conio_v3.2.4.h" /* Funções de console (_setcursortype(), gotoxy()) */
#include "funcoes.h"     /* Declarações das funções */

/* Variáveis globais */
unsigned char arena[ALTURA][LARGURA]; /* Representa a arena do jogo */
int tabua_esq, tabua_dir;             /* Posições das tábuas esquerda e direita */
int bola_x, bola_y;                   /* Posição da bola */
int dx, dy;                           /* Direção da bola */
int vel_tabu = 100, vel_bola = 100;   /* Velocidades das tábuas e da bola */

/* Esconde o cursor do console */
void esconderCursor() 
{
    _setcursortype(_NOCURSOR);
}

/* Move o cursor do console para uma posição específica */
void moverCursor(int x, int y) 
{
    gotoxy(x, y);
}

/* Altera a cor do texto exibido no console */
void mudarCor(int cor) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

/* Inicializa a arena com bordas, tábuas e bola */
void criarCampo() 
{
    int i, j;

    /*Preenche a matriz da arena com bordas e espaços*/ 
    for (i = 0; i < ALTURA; i++) /*definir altura */
    {
        for (j = 0; j < LARGURA; j++) /*definir largura*/
        {
            /*define os cantos*/
            if (i == 0 && j == 0)
            {
                arena[i][j] = CANTO_SUPERIOR_ESQ;
            }
            else if (i == 0 && j == LARGURA - 1)
            {
                arena[i][j] = CANTO_SUPERIOR_DIR;
            }
            else if (i == ALTURA - 1 && j == 0)
            {
                arena[i][j] = CANTO_INFERIOR_ESQ;
            }
            else if (i == ALTURA - 1 && j == LARGURA - 1)
            {
                arena[i][j] = CANTO_INFERIOR_DIR;
            }
            /*define as bordas*/
            else if (i == 0 || i == ALTURA - 1)
            {
                arena[i][j] = BORDA_HORINZONTAL;
            }

            else if (j == 0 || j == LARGURA - 1)
            {
                arena[i][j] = BORDA_VERTICAL;
            }
            else
            {
                arena[i][j] = ' ';
            }
        }
    }

    // Configura posições iniciais das tábuas e da bola
     tabua_esq = ALTURA / 2 - 1;
    tabua_dir = ALTURA / 2 - 1;
    bola_x = ALTURA / 2;
    bola_y = LARGURA / 2;

    /*Define direção inicial da bola (aleatória)*/ 
    dx = (rand() % 2) * 2 - 1; /*Valores possíveis: -1 ou 1*/ 
    dy = (rand() % 2) * 2 - 1;
}

/* Atualiza as tábuas e a bola na matriz da arena */
void atualizarArena() 
{
    int i, j;

    // Limpa o espaço interno da arena
    for (i = 1; i < ALTURA - 1; i++) 
    {
        for (j = 1; j < LARGURA - 1; j++) 
        {
            arena[i][j] = ' ';
        }
    }

    /* Desenha a tábua esquerda */
    for (i = tabua_esq; i < tabua_esq + 3; i++) 
    {
        arena[i][1] = BORDA_VERTICAL;
    }

    /* Desenha a tábua direita */
     for (i = tabua_dir; i < tabua_dir + 3; i++) 
    {
        arena[i][LARGURA - 2] = BORDA_VERTICAL;
    }

    /*Posiciona a bola*/ 
    arena[bola_x][bola_y] = 'O'; /*A bola é representada pelo caractere 'O'*/ 
}

/* Mostra a arena no console */
void mostrarCampo() 
{
    int i, j;
    moverCursor(0, 0); /*Move o cursor para o topo antes de desenhar*/ 

    for (i = 0; i < ALTURA; i++) 
    {
        for (j = 0; j < LARGURA; j++) 
        {
            mudarCor(12); // Cor do texto (vermelho)
            putch(arena[i][j]);
        }
        printf("\n");
    }
}

/* Movimenta as tábuas com base nas teclas pressionadas */
void ajustarTabelas() 
{
    /*mover a tabua esquerda*/
    if (GetAsyncKeyState('A') & 0x8000 && tabua_esq > 1)
    {
        tabua_esq--;
    }
    else if (GetAsyncKeyState('Z') & 0x8000 && tabua_esq < ALTURA - 4)
    {
        tabua_esq++;
    }

    /*move  a tabua direita*/
    if (GetAsyncKeyState(VK_UP) & 0x8000 && tabua_dir > 1)
    {
        tabua_dir--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && tabua_dir < ALTURA - 4)
    {
        tabua_dir++;
    }
}

/* Movimenta a bola e verifica colisões */
void movimentarBola() 
{
    bola_x += dx;
    bola_y += dy;

    /* Verifica colisão com as bordas superiores e inferiores*/
    if (bola_x <= 0 || bola_x >= ALTURA - 1) 
    {
        dx = -dx;
        Beep(1000, 100);
    }

    /*Verifica colisão com as tábuas*/ 
    if (bola_y == 1 && bola_x >= tabua_esq && bola_x < tabua_esq + 3) 
    {
        dy = -dy;
        Beep(800, 100);
    } 
    else if (bola_y == LARGURA - 2 && bola_x >= tabua_dir && bola_x < tabua_dir + 3) 
    {
        dy = -dy;
        Beep(800, 100);
    }

    // Verifica se a bola saiu pelos lados (fim de jogo)
    if (bola_y <= 0 || bola_y >= LARGURA - 1) 
    {
        mudarCor(12); // Vermelho para a mensagem de fim de jogo
        printf("Fim de jogo!\nO jogador %s perdeu!\n", bola_y <= 0 ? "da esquerda" : "da direita");
        exit(0);
    }
}
