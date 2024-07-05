#ifndef _MAPA_H_
#define _MAPA_H_

#define GOAL 'G'
#define VAZIO ','
#define PONTO '.'
#define HEROI '@'
#define FANTASMA 'f'
#define HPAREDE '|'
#define DPAREDE '='
#define PILULA 'p'
#define BOMBA 'b'

struct map
{
    char** mapa;
    int linhas;
    int colunas;

};

struct posicaoMapa
{
    int x;
    int y;
};
typedef struct posicaoMapa POSICAO;
typedef struct map MAPA;

void alocaMapa(MAPA* m);
void lermapa(MAPA* m, char mapa[10]);
void liberarMapa(MAPA* m);
int encontraMapa(MAPA* m, POSICAO* p, char c);
int ehvalida(MAPA* m, int x, int y);
int andavel(MAPA* m, int x, int y);
void andaNoMapa(MAPA* m,int xorigen, int yorigen, int xdestino, int ydestino,char triha );
void copiaMapa(MAPA* origem, MAPA* destino);
int podeandar(MAPA* m, char personagem, int x, int y);
int ehparede(MAPA* m, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);
int verificaMapa(MAPA* m, char c);
#endif