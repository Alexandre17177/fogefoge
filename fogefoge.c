#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;
int venceu;


void Entrada() {
    printf("***FOGE FOGE***");
}
int acabou() {
    POSICAO pos;
    int fogefogenomapa = encontraMapa(&m, &pos, HEROI);
    if (!fogefogenomapa) {
        printf("Voce perdeu!\n");
        return 1;
    }
    else if(venceu) {
        printf("voce venceu!\n");
        return 1;
    }
}
int praondeFantasmaVai (int xatual, int yatual, int* xdestino, int* ydestino) {

    int opcoes[4][2] = {
        {xatual, yatual + 1},
        {xatual +1, yatual },
        {xatual, yatual - 1},
        {xatual - 1, yatual},
    };
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if (podeandar(&m, FANTASMA , opcoes[posicao][0], opcoes[posicao][1]) &&
         !ehpersonagem(&m, GOAL, opcoes[posicao][0], opcoes[posicao][1]) &&
          !ehpersonagem(&m, PILULA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
        return 0;
    }
    return 0;
}
void fantasmas() {
    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++) {
        for(int j = 0; j < m.colunas; j++) {
            if (copia.mapa[i][j] == FANTASMA) {

                int xdestino;
                int ydestino;

                int encontrou = praondeFantasmaVai(i, j, &xdestino, &ydestino);
                if (encontrou) {
                    andaNoMapa(&m, i, j, xdestino, ydestino, PONTO);
                }
            }
        }
    } 
    liberarMapa(&copia);
}
int ehdirecao(char direcao) {
    return direcao == ESQUERDA ||
    direcao == CIMA ||
    direcao == BAIXO ||
    direcao == DIREITA;
}
void move(char direcao) {
    if (!ehdirecao(direcao))
    return;

    int proximox = heroi.x;
    int proximoy = heroi.y;
    switch (direcao)
    {
        case ESQUERDA :
        proximoy--;
        break;
        case CIMA :
        proximox--;
        break;
        case BAIXO :
        proximox++;
        break;
        case DIREITA :
        proximoy++;
        break;
    };
    if(!podeandar(&m, HEROI, proximox, proximoy) || !podeandar(&m, FANTASMA, proximox, proximoy))
    return;
    if(ehpersonagem(&m, PILULA, proximox, proximoy)) {
        tempilula = 1;
    }
    if(ehpersonagem(&m, GOAL,proximox, proximoy)) {
        if(!verificaMapa(&m, PONTO)) {
        venceu = 1; 
        }
        return;
    }
    andaNoMapa(&m, heroi.x, heroi.y, proximox, proximoy, VAZIO);
    heroi.x = proximox;
    heroi.y = proximoy;
    
}
void geraPilula() {
    srand(time(0));
        if (!verificaMapa(&m, PILULA)) {
            int x = rand() % m.linhas;
            int y = rand() % m.colunas;
            if (podeandar(&m, PILULA, x, y)) {
                    m.mapa[x][y] = PILULA;
                }
        }
    
}
void explodePilula() {
    explodePilula2(heroi.x, heroi.y, 0, 1, 3);
    explodePilula2(heroi.x, heroi.y, 0, -1, 3);
    explodePilula2(heroi.x, heroi.y, 1, 0, 3);
    explodePilula2(heroi.x, heroi.y, -1, 0, 3);
    tempilula = 0;
}
void explodePilula2(int x, int y, int somax, int somay, int qtd) {
    if (qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;
    printf(" posição da bomba %d, %d\n", novox, novoy);
        printf(" posição do player %d, %d\n", x, y);

    if(!podeandar(&m, PILULA, novox, novoy)) return;
    
    m.mapa[novox][novoy] = VAZIO;
    explodePilula2(novox, novoy, somax, somay, qtd-1);
}
int main() {
    setlocale(LC_ALL, "portuguese");
    Entrada();
    
    lermapa(&m, "mapa.txt");

    encontraMapa(&m, &heroi, HEROI);
    do
    {
        printf("venceu %d\n", venceu);
        printf("tem pilula: %s\n", (tempilula ? "sim" : "não"));
        imprimirMapa(&m);
        char comando;
        scanf(" %c", &comando);
        move(comando);
        if (comando == BOMBA && tempilula) explodePilula();
        if (tempilula) geraPilula();
        fantasmas();
    } while (!acabou());
    imprimirMapa(&m);
    
}