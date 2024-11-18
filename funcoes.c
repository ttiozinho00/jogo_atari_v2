/*funcoes.c*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "funcoes.h"

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
void esconderCursor() 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/*Função para definir a posição do cursor*/ 
void moverCursor(int x, int y) 
{
    COORD coord;
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*Função para alterar a cor do texto*/ 
void mudarCor(int cor) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

/*Função para inicializar a arena*/ 
void criarCampo() 
{
	int i;
	int j;

    for (i = 0; i < LINHAS; i++) 
    {
        for (j = 0; j < COLUNAS; j++) 
        {
            if (i == 0 || i == LINHAS - 1 || (j == 0 && (i < 6 || i >= 14)) || (j == COLUNAS - 1 && (i < 6 || i >= 14))) 
            {
                arena[i][j] = '='; /*Paredes e buracos*/ 
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
void mostrarCampo() 
{
	int i;
	int j;

    system("cls");
    moverCursor(0, 0);
    for (i = 0; i < LINHAS; i++) 
    {
        for (j = 0; j < COLUNAS; j++) 
        {
            if (j == 1 && i >= tabu_esq && i < tabu_esq + 3) 
            {
                mudarCor(11); /*Azul claro para a tábua esquerda*/ 
                printf("|"); /* Linha vertical em UTF-8 */ 
            } 

            else if (j == COLUNAS - 2 && i >= tabu_dir && i < tabu_dir + 3) 
            {
                mudarCor(14); /*Amarelo para a tábua direita*/ 
                printf("|");
            } 

            else if (i == bola_x && j == bola_y) 
            {
                mudarCor(12); /*Vermelho para a bola*/ 
                printf("O");
            } 

            else 
            {
                mudarCor(7); /*Branco para o restante*/ 
                printf("%c", arena[i][j]);
            }
        }
        printf("\n");
    }
}

/*Função para mover as tábuas*/ 
void ajustarTabelas() 
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
void movimentarBola() 
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

    if (bola_y <= 0 || bola_x >= COLUNAS -1)
    {
        if (bola_y <= 0)
        {
            printf("Jogador da Direita Ganhou!!\n");
        }

        else
        {
            printf("Jogador da Esquerda Ganhou!!\n");   
        }
    }

    if (bola_y <= 0 || bola_y >= COLUNAS - 1) 
    {
        mudarCor(12);
        printf("Fim de jogo!\n");
        printf("O jogador %s perdeu!\n", bola_y <= 0 ? "da esquerda" : "da direita");
        exit(0);
    }
}
