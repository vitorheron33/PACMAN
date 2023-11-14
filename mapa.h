#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define FANTASMA 'F'
#define PILULA 'P'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'

struct matriz{
    char** mapa;  //[5][10+1]; //10+1 para que seja identificado o \0 no final de cada linha
    int linhas;
    int colunas;
};

typedef struct matriz MAPA;

struct posicao{
    int x;
    int y;
};

typedef struct posicao POSICAO;

//Assinatura das funções
void libera_mapa(MAPA* m);
void le_mapa(MAPA* m);
void aloca_mapa(MAPA* m);
void imprime_mapa(MAPA* m);
int encontra_no_mapa(MAPA* m, POSICAO* p, char c);
int ehvalida (MAPA* m, int x, int y);
int ehvazio (MAPA* m, int x, int y);
int ehparede (MAPA* m, int x, int y);
int ehpersonagem(MAPA* m,char personagem,int x,int y);
int pode_andar(MAPA* m, char personagem , int x, int y);
void andanomapa (MAPA* m, int xorigem, int yorigem,
                 int xdestino, int ydestino);
void copiamapa (MAPA* destino, MAPA* origem);

#endif
