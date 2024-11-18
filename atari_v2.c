/*
* gcc -o atari_v2 atari_v2.c conio_v3.2.4.c funcoes.c -Wall -pedantic -Wextra -Werror
*/

/* 
   Programa: Jogo Atari v2 (Estilo Pong)
   Descrição: Este programa implementa um jogo estilo Pong, onde dois jogadores controlam tábuas para 
              rebater uma bola que se move pela tela. O objetivo é evitar que a bola ultrapasse a tábua 
              do seu lado, pontuando quando isso acontece. A movimentação da bola e das tábuas são baseadas 
              em entradas do teclado e o jogo é exibido em um console de texto.

   Funcionalidades:
   - Controla duas tábuas que podem ser movidas para cima ou para baixo com as teclas de direção.
   - A bola se move automaticamente e pode colidir com as bordas da tela e com as tábuas.
   - A velocidade da bola pode ser ajustada.
   - O jogo continua em loop até ser interrompido manualmente.

   Exemplos de uso:
   - Ativar o programa: Executar o arquivo `atari_v2.exe` no terminal.
   - O jogo será iniciado automaticamente, e as tábuas podem ser controladas com as teclas de direção.
   
   Observações:
   - O programa depende da biblioteca `conio_v3.2.4.h` para manipulação de elementos gráficos no console e `funcoes.h` 
     para funções auxiliares como a movimentação da bola e das tábuas.
   - O jogo é exibido em um console de texto, e não possui uma interface gráfica.
   - A velocidade da bola pode ser controlada através da variável `vel_bola`, definida em `funcoes.h`.

   Programador: []
   RGM: []
   Data da última modificação: []
*/


/*atari_v2.c*/
#include <stdio.h>       /* printf() */
#include <stdlib.h>      /* system() */
#include <time.h>        /* time(), srand() */
#include <windows.h>     /* Sleep() */
#include "conio_v3.2.4.h" /* Funções de console (_setcursortype()) */
#include "funcoes.h"     /* Declarações das funções */


int main(int argc, char const *argv[])
{
    argv = argv;
    argc = argc;
    
    system("chcp 850 > nul");
	srand(time(NULL));
    esconderCursor();
    criarCampo();

    while (1) 
    {
        mostrarCampo();      /*Exibe a arena no console*/ 
        ajustarTabelas();    /*Move as tábuas com base nas teclas pressionadas*/ 
        movimentarBola();    /*Move a bola e verifica colisões*/ 
        Sleep(vel_bola);     /*Controla a velocidade da bola*/ 
    }

	return 0;
}

