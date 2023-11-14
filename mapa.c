#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void le_mapa(MAPA* m){

    FILE* f;
    f = fopen("mapa.txt","r");
        if (f==0){ //tratamentto de erro
            printf("Erro de leitura do arquivo do m->mapa! \n");
            exit(1);
        }

    fscanf(f,"%d %d",&m->linhas,&m->colunas);

    aloca_mapa(m);

    int i;
    for (i = 0; i<5; i++){
        fscanf(f,"%s",m->mapa[i]);
    }
    fclose(f);
}

int encontra_no_mapa(MAPA* m, POSICAO* p, char c){
    int i;
    int j;
    for (i=0;i<m->linhas;i++){
        for (j=0;j<m->colunas;j++){
            if (m->mapa[i][j]== c ){
                p->x=i;
                p->y=j;
                return 1;
            }
        }
    }
    return 0;
}

void aloca_mapa(MAPA* m){
    m->mapa = malloc(sizeof(char*)*m->linhas);
    int j;
    for (j=0;j<m->linhas;j++){
    m->mapa[j] = malloc(sizeof(char*)*(m->colunas+1));
    }
}

void libera_mapa(MAPA* m){

    int i;
    for (i=0;i<m->linhas;i++){
        free(m->mapa[i]);
    }
    free(m->mapa);
}

int ehvalida (MAPA* m, int x, int y){
    if (x>=m->linhas || y>=m->colunas)
        return 0;

    return 1;
}

int ehvazio (MAPA* m, int x, int y){
    return m->mapa[x][y] == VAZIO;
}

int ehparede (MAPA* m, int x, int y){
    return
        m->mapa[x][y] == PAREDE_HORIZONTAL ||
        m->mapa[x][y] == PAREDE_VERTICAL;
}

int ehpersonagem(MAPA* m,char personagem,int x,int y){
    return
        m->mapa[x][y] == personagem;
}

int pode_andar(MAPA* m, char personagem , int x, int y){
    return
        ehvalida(m,x,y) &&
        !ehparede(m,x,y)&&
        !ehpersonagem(m,personagem,x,y);
}

void andanomapa (MAPA* m, int xorigem, int yorigem,
                 int xdestino, int ydestino){

    char personagem = m->mapa[xorigem][yorigem];
    m->mapa[xdestino][ydestino] = personagem;
    m->mapa[xorigem][yorigem] = VAZIO;
}

void copiamapa (MAPA* destino, MAPA* origem){

    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    aloca_mapa(destino);

	int i;
    for ( i=0 ; i < origem->linhas ; i++){
        strcpy(destino->mapa[i], origem->mapa[i]);
    }
}
