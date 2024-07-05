#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

int verificaMapa(MAPA* m, char c) {
    for (int i = 0; i < m->linhas; i++) {
    for (int j = 0; j < m->colunas; j++){
        if (m->mapa[i][j] == c) {
            printf("oi %d %d\n", i, j);
            return 1;
            }
        }     
    }
    return 0;
}
int ehparede(MAPA* m, int x, int y) {
    return
        m->mapa[x][y] == HPAREDE ||
        m->mapa[x][y] == DPAREDE;
}
int ehpersonagem(MAPA* m, char personagem, int x, int y) {
    return
    m->mapa[x][y] == personagem;
}
int podeandar(MAPA* m, char personagem, int x, int y) {
    return 
        ehvalida(m, x, y) &&
        !ehparede(m, x, y) &&
        !ehpersonagem(m, personagem, x, y);
}
void copiaMapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocaMapa(destino);
    for(int i = 0; i < origem->linhas; i++) {
        strcpy(destino->mapa[i], origem->mapa[i]);
    }    
}
void alocaMapa(MAPA* m) {
        m->mapa = malloc(sizeof(char*) * m->linhas);
    for (int i = 0; i < m->linhas; i++) {
        m->mapa[i] = malloc(sizeof(char*) * m->colunas+1);
    }

}
void lermapa(MAPA* m, char mapa[10]) {
    FILE* f;
    f = fopen(mapa, "r");

    if (f == 0) {
        printf("erro na leitura do mapa\n");
        exit(1);
    }

    
    fscanf(f, "%d %d", &m->linhas, &m->colunas);
    printf("linhas %d colunas %d\n", m->linhas, m->colunas);

    alocaMapa(m);
//
    for (int i = 0; i < m->linhas; i++) {
         fscanf(f, "%s", m->mapa[i]);
    }
    fclose(f);
}
void liberarMapa(MAPA* m) {
        for (int i = 0; i < m->linhas; i++) {
    free(m->mapa[i]);
    }
    free(m->mapa);

}

int encontraMapa(MAPA* m, POSICAO* p, char c) {
        for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            if(m->mapa[i][j] == c) {
            p->x = i;
            p->y = j;
            printf("achou o @ em %d %d\n", p->x, p->y);
            return 1;
            }
        }
    }
    return 0;
}
int ehvalida(MAPA* m, int x, int y) {
    if (x >= m->linhas)
        return 0;
    if (y >= m->colunas)
        return 0;

    return 1;
}
int andavel(MAPA* m, int x, int y) {
    if (m->mapa[x][y] == VAZIO || m->mapa[x][y] == PONTO)
    return 1;
}
void andaNoMapa(MAPA* m,int xorigen, int yorigen, int xdestino, int ydestino,char trinha ) {
    char personagem = m->mapa[xorigen][yorigen];
    m->mapa[xdestino][ydestino] = personagem;
    m->mapa[xorigen][yorigen] = trinha;
}