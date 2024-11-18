/*funcoes.h*/
#ifndef FUNCOES_H
#define FUNCOES_H

#include <windows.h>

/* Constantes */
#define ALTURA 20
#define LARGURA 40
#define TAM_BURACO 8

/* Variáveis globais */
extern char campo[ALTURA][LARGURA];
extern int tab_esq, tab_dir;
extern int bola_x, bola_y;
extern int dir_x, dir_y;
extern int atraso_tab, atraso_bola;
extern int vel_tabu, vel_bola;

/* Funções */
void esconderCursor();
void moverCursor(int, int);
void mudarCor(int);
void criarCampo();
void mostrarCampo();
void ajustarTabelas();
void movimentarBola();

#endif

