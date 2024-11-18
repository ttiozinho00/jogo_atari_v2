/*funcoes.h*/
#ifndef FUNCOES_H
#define FUNCOES_H

/* Constantes */
#define ALTURA 20
#define LARGURA 40
/* Caracteres ASCII para bordas */
#define BORDA_HORINZONTAL 205
#define BORDA_VERTICAL 186
#define CANTO_SUPERIOR_ESQ 201
#define CANTO_SUPERIOR_DIR 187
#define CANTO_INFERIOR_ESQ 200
#define CANTO_INFERIOR_DIR 188

/* Variáveis globais */
extern unsigned char arena[ALTURA][LARGURA];
extern int tabua_esq, tabua_dir;
extern int bola_x, bola_y;
extern int dx, dy;
extern int vel_tabu, vel_bola;

/* Protótipos das funções */
void esconderCursor();
void moverCursor(int x, int y);
void mudarCor(int cor);
void criarCampo();
void atualizarArena();
void mostrarCampo();
void ajustarTabelas();
void movimentarBola();

#endif
