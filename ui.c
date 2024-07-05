#include <stdlib.h>
#include <stdio.h>
#include "ui.h"
#include "mapa.h"

char desenhoParede[4][8] = {
    {"/-----\\"},
    {"|.....|" },
    {"|.....|" },
    {"\\-----/"}
};
char desenhoVazio[4][8] = {
    {"     - "},
    {" -     "},
    {"  -    "},
    {"      -"}
};
char desenhoFantasma[4][8] = {
    {" /----/" },
    {"| * * |" },
    {"| www |" },
    {"\\_____/"}
};
char desenhoHeroi[4][8] = {
    {"._w_w_."   },
    {"| @ @ |"   },
    {"|  _  |"   },
    {"\\_/ \\_/" }
};
char desenhoPilula[4][8] = {
    {"       " },
    {"/----\\ "},
    {"\\----/ "},
    {"       " }
};
char desenhoPonto[4][8] = {
    {"       " },
    {"  .-.  "},
    {"  ._.  "},
    {"       " }
};
char desenhoGoal[4][8] = {
    {" ######" },
    {" # || #" },
    {" # || #" },
    {" ######" }
};


void imprimeParte(char desenho[4][8], int parte) {
    printf("%s", desenho[parte]);
}

void imprimirMapa(MAPA* m) {
    for (int i = 0;i < m->linhas; i++) {
        for (int parte = 0; parte < 4; parte++) {
            for (int j = 0; j < m->colunas; j++){
                 
                 switch (m->mapa[i][j]){
                 case FANTASMA:
                    imprimeParte(desenhoFantasma, parte);
                    break;
                    
                 case HEROI:
                    imprimeParte(desenhoHeroi, parte);
                    break;

                 case VAZIO:
                    imprimeParte(desenhoVazio, parte);
                    break;

                 case PONTO :
                    imprimeParte(desenhoPonto, parte);
                    break;
                    
                 case HPAREDE :
                 case DPAREDE :
                    imprimeParte(desenhoParede, parte);
                    break;

                 case PILULA:
                    imprimeParte(desenhoPilula, parte);
                    break;

                    case GOAL :
                    imprimeParte(desenhoGoal, parte);
                    break;

                 }
            }
            printf("\n");
            
        }
    }
}