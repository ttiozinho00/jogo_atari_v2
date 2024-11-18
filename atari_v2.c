/*
* conpilar: gcc -o atari_v2 atari_v2.c funcoes.c -Wall -pedantic -Wextra -Werror
*/

/*atari_v2.c*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "funcoes.h"


int main(int argc, char const *argv[])
{
    argv = argv;
    argc = argc;
    
    SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL));
    esconderCursor();
    criarCampo();

    while (1) 
    {
        mostrarCampo();
        ajustarTabelas();
        movimentarBola();
        Sleep(vel_bola);
    }

	return 0;
}
