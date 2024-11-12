/* Dica de como compilar: gcc atari.c conio_v3.2.4.c -o atari -Wall -pedantic -Wextra -Werror */

/* bibliotecas padrao em c */
#include <stdio.h> /* printf(), scanf() */
#include <stdlib.h> /* srand(), rand(), NULL */
#include <time.h> /* time() */
#include <windows.h> /* Sleep()  */

/* biblioteca utilizada */
#include "conio_v3.2.4.h" /* gotoxy(), getch(), clrscr(), kbhit(), _setcursortype() */

/*diretivas de pré-compilação*/
#define ESPACO 32
#define ESC 27
#define MISSIL 220
#define LINHA_INICIAL 29
#define COLUNA_INICIAL 60
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define CANHAO 219
#define LIMITE_ESQUERDA 20
#define LIMITE_DIREITA 100
#define CARACTER_SUPERIOR_DIREITO 187
#define CARACTER_SUPERIOR_ESQUERDO 201
#define CARACTER_INFERIOR_ESQUERDO 200
#define CARACTER_INFERIOR_DIREITO 188
#define TRACO_HORIZONTAL 205
#define TRACO_VERTICAL 186
#define POSICAO_MIRA_LINHA_INICIAL 15
#define LIMITE_MIRA_CIMA 2
#define LIMITE_MIRA_BAIXO 26
#define LINHA_ESPACO_INICIAL 28

/* inicio */
int main(int argc, char const *argv[])
{
    /* variaveis locais */
    int linha, coluna, tecla, i, conf = 0, posX_ini1 = 2, posX_ini2 = 2;
    int posL_mira, j, posL_bala, posX_ini3 = 2, temp_mira = 0,vel_canhao;
    int vel_mira, posY_ini1, posC_tiro, posL_mira_tiro, temp_bala = 0;
    int posX_ini5 = 2, posY_ini2, posY_ini3, ativador = 0, vel_missil;
    int posX_ini4 = 2, temp_missil = 0, temp_pow = 0, temp_canhao = 0;
    int pontos = 0, limC_pow_janela, posY_ini4, posY_ini5, vel_bala;
    int posX_ini6 = 2, posY_ini6, posX_ini7 = 2, posY_ini7;
    int posX_ini8 = 2, posY_ini8, posX_ini9 = 2, posY_ini9;

	/* silenciar parametro */
    argc = argc;
    argv = argv;

    /* tempo do deslocamento em milisegundos da */
    printf("tempo de deslocamento do canhao em ms:");
    scanf("%d", &vel_canhao);
    printf("tempo de deslocamento da mira em ms:");
    scanf("%d", &vel_mira);
    printf("tempo de deslocamento da bala em ms:");
    scanf("%d", &vel_bala);
    printf("tempo de deslocamento do missil em ms:");
    scanf("%d", &vel_missil);

    /* limpa tela */
    clrscr();

    /* variaveis q vai receber a posicao inicial */
    linha = LINHA_INICIAL;
    coluna = COLUNA_INICIAL;
    posL_mira = POSICAO_MIRA_LINHA_INICIAL;
    posL_bala = LINHA_ESPACO_INICIAL;

    /* printar um caracter no canto superior esquerdo para definir o limite */
    gotoxy( LIMITE_ESQUERDA, 1 );
    printf("%c", CARACTER_SUPERIOR_ESQUERDO);

    /* printar caracter inferior esquerdo */
    gotoxy ( LIMITE_ESQUERDA, 30 );
    printf("%c", CARACTER_INFERIOR_ESQUERDO);

    /* pritar caracter superior direito */
    gotoxy( LIMITE_DIREITA, 1 );
    printf("%c", CARACTER_SUPERIOR_DIREITO);

    /* printar caracter inferior direito */
    gotoxy(LIMITE_DIREITA, 30);
    printf("%c", CARACTER_INFERIOR_DIREITO);

    /* laco para printar traco vertical do lado esquerdo */
    for(i = 2; i < 30; i++)
    {
        gotoxy(LIMITE_ESQUERDA, i);
        printf("%c", TRACO_VERTICAL);
    }

    /* laco para printar traco vertical do lado direito*/
    for(i = 2; i < 30; i++)
    {
        gotoxy(LIMITE_DIREITA, i);
        printf("%c", TRACO_VERTICAL);
    }

    /* laco para printar traco horizontal superior */
    for(j = LIMITE_ESQUERDA + 1; j < LIMITE_DIREITA; j++)
    {
        gotoxy( j, 1 );
        printf("%c", TRACO_HORIZONTAL);
    }

    /* loco para printar traco horizontal inferior */
    for(j = LIMITE_ESQUERDA + 1; j < LIMITE_DIREITA; j++)
    { 
        gotoxy( j, 30);
        printf("%c", TRACO_HORIZONTAL);
    }

    /* tirar o cursor da tela */
    _setcursortype(_NOCURSOR);

    srand(time(NULL));

    /* posicao aleatoria da coluna nos limites de janela */
    posY_ini1 = rand() % (99 + 1 - 21) + 21;

    posY_ini2 = rand() % (99 + 1 - 21) + 21;

    posY_ini3 = rand() % (99 + 1 - 21) + 21;

    posY_ini4 = rand() % (99 + 1 -21) + 21;

    posY_ini5 = rand() % (99 + 1 -21) + 21;

    /* inicia os cinco misseis padroes */
    gotoxy(posY_ini1, posX_ini1);
    printf("%c", MISSIL);
    gotoxy(posY_ini2, posX_ini2);
    printf("%c", MISSIL);
    gotoxy(posY_ini3, posX_ini3);
    printf("%c", MISSIL);
    gotoxy(posY_ini4, posX_ini4);
    printf("%c", MISSIL);
    gotoxy(posY_ini5, posX_ini5);
    printf("%c", MISSIL);
  
    /* posicao para printar a mira na tela */
    gotoxy( coluna, posL_mira);
    printf("x");

    /* posicao para printar o canhao na tela */
    gotoxy( coluna, linha );
    printf("%c", CANHAO);
    
    /* loop infinito */
    for( ; ; )
    {
    
        /* contagem dos pontos */
        gotoxy(79, 1);
        printf("[PONTOS: %d]", pontos);
    
        /* condicao para ganhar o jogo */
        if(pontos == 50)
        {
            gotoxy(60, 13);
            printf("YOU WIN!!");
            break;
        }
  
        /* tempo de execucao em ms */
        Sleep(1);
    
        /* atualiza tempo da mira */
        temp_mira++;
    
        /* atualiza tempo do missil */
        temp_missil++; 

        /* atualiza tempo da bala */
        temp_bala++;

        /* atualiza tempo do canhao */
        temp_canhao++;
    
        /* quando der o pow comecar a contar o tempo de pow na tela */
        if(ativador == 1)
        {
            temp_pow++;
        }

        /*  */
        if(temp_missil == vel_missil)
        {
            temp_missil = 0;
            gotoxy(posY_ini1, posX_ini1);
            printf(" ");
            gotoxy(posY_ini2, posX_ini2);
            printf(" ");
            gotoxy(posY_ini3, posX_ini3);
            printf(" ");
            gotoxy(posY_ini4, posX_ini4);
            printf(" ");
            gotoxy(posY_ini5, posX_ini5);
            printf(" ");

            /* apaga a posicao do sexto missil quando pontos for >= 12 pontos */
            if(pontos >= 12)
            {
                gotoxy(posY_ini6, posX_ini6);
                printf(" ");
            }

            /* apaga a posicao do setimo missil quando pontos for >= 24 pontos */
            if(pontos >= 24)
            {
                gotoxy(posY_ini7, posX_ini7);
                printf(" ");
            }

            /* apaga a posicao do setimo missil quando pontos for >= 35 pontos */
            if(pontos >= 35)
            {
                gotoxy(posY_ini8, posX_ini8);
                printf(" ");
            }

            /* apaga a posicao do setimo missil quando pontos for >= 46 pontos */
            if(pontos >= 46)
            {
                gotoxy(posY_ini9, posX_ini9);
                printf(" ");
            }
            posX_ini1++;
            posX_ini2++;
            posX_ini3++;
            posX_ini4++;
            posX_ini5++;

            /* atualiza posicao do sexto missil quando pontos >= 12 */
            if(pontos >= 12)
            {
                posX_ini6++;
            }

            /* atualiza a posicao do setimo missil se pontos >= 24 */
            if(pontos >= 24)
            {
                posX_ini7++;
            }

            /* atualiza a posicao do oitavo missil se pontos >= 36 */
            if(pontos >= 35)
            {
                posX_ini8++;
            }

            /* atualiza a posicao do oitavo missil se pontos >= 46 */
            if(pontos >= 46)
            {
                posX_ini9++;
            }
            /* printar os cinco misseis padrao na posicao atualizada */
            gotoxy(posY_ini1, posX_ini1);
            printf("%c", MISSIL);
            gotoxy(posY_ini2, posX_ini2);
            printf("%c", MISSIL);
            gotoxy(posY_ini3, posX_ini3);
            printf("%c", MISSIL);
            gotoxy(posY_ini4, posX_ini4);
            printf("%c", MISSIL);
            gotoxy(posY_ini5, posX_ini5);
            printf("%c", MISSIL);

            /* printa o sexto missil na posicao atualizada qdo pontos >= 12 na posicao atualizada */
            if(pontos >= 12 )
            {
                gotoxy(posY_ini6, posX_ini6);
                printf("%c", MISSIL);
            }

            /* printar o setimo missil quando pontos >= 24 na posicao atualizada */
            if(pontos >= 24)
            {
                gotoxy(posY_ini7, posX_ini7);
                printf("%c", MISSIL);
            }

      /* printar o oitavo missil quando pontos >= 35 na posicao atualizada */
      if(pontos >= 35)
      {
        gotoxy(posY_ini8, posX_ini8);
        printf("%c", MISSIL);
      }

      /* printar o oitavo missil quando pontos >= 35 na posicao atualizada */
      if(pontos >= 46)
      {
        gotoxy(posY_ini9, posX_ini9);
        printf("%c", MISSIL);
      }
    }
    
    /* condicao de cada missil de perder o */
    if(posX_ini1 == 29 || (posY_ini1 == coluna && posX_ini1 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!!");
      break;
    }
    if(posX_ini2 == 29 || (posY_ini2 == coluna && posX_ini2 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }

    if(posX_ini3 == 29 || (posY_ini3 == coluna && posX_ini3 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }
    
    if(posX_ini4 == 29 || (posY_ini4 == coluna && posX_ini4 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }

    if(posX_ini5 == 29 || (posY_ini5 == coluna && posX_ini5 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }
    if(posX_ini6 == 29 || (posY_ini6 == coluna && posX_ini6 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }
     if(posX_ini7 == 29 || (posY_ini7 == coluna && posX_ini7 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }
     if(posX_ini8 == 29 || (posY_ini8 == coluna && posX_ini8 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }
     if(posX_ini9 == 29 || (posY_ini9 == coluna && posX_ini9 == 28))
    {
      gotoxy(60 , 13);
      printf("GAME OVER!");
      break;
    }
     /* identificar tecla se digitado */
    if( kbhit() )
    {
      /* pega o codigo do caracter digitado */
      tecla = getch();

      /* qdo der espaco atualizar posicoes */
      if(tecla == ESPACO )
      {
        /* confirmador de tecla espaco */
        conf = 1;

        /* atualizar pos coluna do tiro */
        posC_tiro = coluna;

        /* atualiza a pos de tiro da linha da mira */
        posL_mira_tiro = posL_mira;

        /* pos da bala volta ao inicio */
        posL_bala = 28;
      }
      
    }
    /* tempo para o pow apagar da tela */
    if(temp_pow == 300)
    {
      /* reseta o tempo */
      temp_pow = 0;

      /* reseta o ativador de tempo */
      ativador = 0;

      /* apagar pow */
      gotoxy(limC_pow_janela, posL_mira_tiro);
      printf("   ");

      /* quando apagar 'POW' colocar a mira de volta */
      gotoxy(coluna, posL_mira);
      printf("x");
    }

    /* confirmador de tecla espaco */
    if(conf == 1)
    {
      /* printar bala na posicao onde foi atirado */
      gotoxy(posC_tiro, posL_bala);
      printf("O");

      /* tempo da bala em ms e decremento da posicao linha da bala em que foi atirado */
      if(temp_bala >= vel_bala)
      {
        temp_bala = 0;
        gotoxy(posC_tiro, posL_bala);
        printf(" ");
        posL_bala--;
      }

      /* quando pos linha da bala == linha da mira de quando foi atirado */
      if( posL_bala == posL_mira_tiro )
      {
        limC_pow_janela = posC_tiro - 1;

        if(posC_tiro - 1 == 20)
        {
          limC_pow_janela = posC_tiro;
        }

        if(posC_tiro + 1 == 100)
        {
          limC_pow_janela = posC_tiro - 2;
        }

        gotoxy(limC_pow_janela, posL_mira_tiro);
        printf("POW");
        
        /* ativar contagem do pow na tela */
        ativador = 1;
        
        /* difinicao da area da explosao para cada inimigo */
        if((posX_ini1 >= posL_mira_tiro - 4 && posX_ini1 <= posL_mira_tiro + 4 ) && (posY_ini1 >= posC_tiro - 4 && posY_ini1 <= posC_tiro + 4))
        {
          pontos++;
          
          gotoxy(posY_ini1, posX_ini1);
          printf(" ");
          posY_ini1 = rand() % (99 + 1 - 21) + 21;
          posX_ini1 = 2; 
        }
        if((posX_ini2 >= posL_mira_tiro - 4 && posX_ini2 <= posL_mira_tiro + 4 ) && (posY_ini2 >= posC_tiro - 4 && posY_ini2 <= posC_tiro + 4))
        {
          pontos++;
          
          gotoxy(posY_ini2, posX_ini2);
          printf(" ");
          posY_ini2 = rand() % (99 + 1 - 21) + 21;
          posX_ini2 = 2; 
        }
        if((posX_ini3 >= posL_mira_tiro - 4 && posX_ini3 <= posL_mira_tiro + 4 ) && (posY_ini3 >= posC_tiro - 4 && posY_ini3 <= posC_tiro + 4))
        {
          pontos++;
         
          gotoxy(posY_ini3, posX_ini3);
          printf(" ");
          posY_ini3 = rand() % (99 + 1 - 21) + 21;
          posX_ini3 = 2; 
        }
        if((posX_ini4 >= posL_mira_tiro - 4 && posX_ini4 <= posL_mira_tiro + 4 ) && (posY_ini4 >= posC_tiro - 4 && posY_ini4 <= posC_tiro + 4))
        {
          pontos++;
         
          gotoxy(posY_ini4, posX_ini4);
          printf(" ");
          posY_ini4 = rand() % (99 + 1 - 21) + 21;
          posX_ini4 = 2; 
        }
        if((posX_ini5 >= posL_mira_tiro - 4 && posX_ini5 <= posL_mira_tiro + 4 ) && (posY_ini5 >= posC_tiro - 4 && posY_ini5 <= posC_tiro + 4))
        {
          pontos++;
          
          gotoxy(posY_ini5, posX_ini5);
          printf(" ");
          posY_ini5 = rand() % (99 + 1 - 21) + 21;
          posX_ini5 = 2; 
        }
        if((posX_ini6 >= posL_mira_tiro - 4 && posX_ini6 <= posL_mira_tiro + 4 ) && (posY_ini6 >= posC_tiro - 4 && posY_ini6 <= posC_tiro + 4))
        {
          pontos++;
          gotoxy(posY_ini6, posX_ini6);
          printf(" ");
          posY_ini6 = rand() % (99 + 1 - 21) + 21;
          posX_ini6 = 2; 
        }
        if((posX_ini7 >= posL_mira_tiro - 4 && posX_ini7 <= posL_mira_tiro + 4 ) && (posY_ini7 >= posC_tiro - 4 && posY_ini7 <= posC_tiro + 4))
        {
          pontos++;
          gotoxy(posY_ini7, posX_ini7);
          printf(" ");
          posY_ini7 = rand() % (99 + 1 - 21) + 21;
          posX_ini7 = 2; 
        }
        if((posX_ini8 >= posL_mira_tiro - 4 && posX_ini8 <= posL_mira_tiro + 4 ) && (posY_ini8 >= posC_tiro - 4 && posY_ini8 <= posC_tiro + 4))
        {
          pontos++;
          gotoxy(posY_ini8, posX_ini8);
          printf(" ");
          posY_ini8 = rand() % (99 + 1 - 21) + 21;
          posX_ini8 = 2; 
        }
        if((posX_ini9 >= posL_mira_tiro - 4 && posX_ini9 <= posL_mira_tiro + 4 ) && (posY_ini9 >= posC_tiro - 4 && posY_ini9 <= posC_tiro + 4))
        {
          pontos++;
          gotoxy(posY_ini9, posX_ini9);
          printf(" ");
          posY_ini9 = rand() % (99 + 1 - 21) + 21;
          posX_ini9 = 2; 
        }
        /* resetar confirmador de espaco */
        conf = 0;

        /* condicaoes para pontos */
        switch (pontos)
        {
          /* inicia um sexto missil se pontos == 12 */
          case 12:
            posY_ini6 = rand() % (99 + 1 - 21) + 21;
            gotoxy(posY_ini6, posX_ini6);
            printf("%c", MISSIL);
            break;

          /* inicia um setimo missil se pontos == 24 */
          case 24:
            posY_ini7 = rand() % (99 + 1 - 21) + 21;
            gotoxy(posY_ini7, posX_ini7);
            printf("%c", MISSIL);
            break;

          /* inicia um oitavo missil se pontos == 35  */
          case 35:
            posY_ini8 = rand() % (99 + 1 - 21) + 21;
            gotoxy(posY_ini8, posX_ini8);
            printf("%c", MISSIL);
            break;

          /* inicia um nono missil se pontos == 45  */
          case 46:
            posY_ini8 = rand() % (99 + 1 - 21) + 21;
            gotoxy(posY_ini8, posX_ini8);
            printf("%c", MISSIL);
            break;

          /* aumentar a velocidade de queda do missil em 40ms a cada 9 pontos */
          case 9:
            vel_missil = vel_missil - 40;
            temp_missil = 0;
            break;
        
          case 18:
            vel_missil = vel_missil - 40;
            temp_missil = 0;
            break;

          case 27:
            vel_missil = vel_missil - 40;
            temp_missil = 0;
            break;

          case 36:
            vel_missil = vel_missil - 40;
            temp_missil = 0;
            break;
            
          case 45:
            vel_missil = vel_missil - 40;
            temp_missil = 0;
            break;
        }
      }
    } 

    /* tecla especial */
    if( !tecla )
  	{
      tecla = getch(); 
        switch( tecla )
        {
          case SETA_ESQUERDA:
            
            if(temp_canhao > vel_canhao)
            {
              gotoxy(coluna, linha);
              printf(" ");

              gotoxy(coluna, posL_mira);
              printf(" ");
              /* atualizacao da coluna se digitar seta para esquerda ate o limite da area */
              if(coluna > LIMITE_ESQUERDA + 1)
              {
                coluna--;
              }
              gotoxy(coluna, linha);
              printf("%c", CANHAO);

              gotoxy(coluna, posL_mira);
              printf("x");
              temp_canhao = 0;
            }
          break;

        case SETA_DIREITA: 

          if(temp_canhao > vel_canhao)
          {
            /* apagar caracter canhao da tela */
            gotoxy(coluna, linha);
            printf(" ");

            /* apaga o caracter mira da tela */
            gotoxy(coluna, posL_mira);
            printf(" ");

            /* atualizar a posicao ate o limite da area */
            if(coluna < LIMITE_DIREITA - 1)
            {
              coluna++;
            }
            gotoxy(coluna, linha);
            printf("%c", CANHAO);

            gotoxy(coluna, posL_mira);
            printf("x");
            temp_canhao = 0;
          }
          break;

        case SETA_CIMA:

          if(temp_mira > vel_mira)
          {
            /* apagar o caracter x da tela */
            gotoxy(coluna, posL_mira);
            printf(" ");
            if(posL_mira > LIMITE_MIRA_CIMA)
            {
              posL_mira--;
            }   
            gotoxy( coluna, posL_mira);
            printf("x");
            temp_mira = 0;
          }
          break;

        case SETA_BAIXO:
          if(temp_mira > vel_mira)
          {
            /* apagar a mira da tela */
            gotoxy(coluna, posL_mira);
            printf(" ");

            /* atualiza a posicao linha da mira */
            if(posL_mira < LIMITE_MIRA_BAIXO)
            {
              posL_mira++;
            }  
            gotoxy(coluna, posL_mira);
            printf("x");
            temp_mira = 0;
          }
          break;
        }
    }
    /* caso a tecla ESC for digita sair do programa */
    if( tecla == ESC )
    {
      break;
    }
  }
  /* voltar o cursor para tela */
  _setcursortype(_NORMALCURSOR);
  return 0;
}
