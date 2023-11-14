#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "foge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int acabou(){
    POSICAO pos;

    int perdeu = !encontra_no_mapa(&m,&pos,HEROI);
    int ganhou = !encontra_no_mapa(&m,&pos,FANTASMA);

    return ganhou || perdeu;
}

int ehdirecao (char comando){
    return
        comando == ESQUERDA ||
        comando == CIMA ||
        comando == BAIXO ||
        comando == DIREITA;
}

void move_pers(char comando){

    if (!ehdirecao(comando))
            return;

    int prox_x = heroi.x;
    int prox_y = heroi.y;

    switch (comando){
        case ESQUERDA:
            prox_y--;
            break;
        case CIMA:
            prox_x--;
            break;
        case BAIXO:
            prox_x++;
            break;
        case DIREITA:
            prox_y++;
            break;
    }

    if (!pode_andar(&m, HEROI, prox_x, prox_y))
        return;

    if (ehpersonagem(&m, PILULA, prox_x, prox_y))
        tempilula=1;

    andanomapa(&m, heroi.x, heroi.y, prox_x, prox_y);

    heroi.x = prox_x;
    heroi.y = prox_y;
}

void fantasma(){

    MAPA copia;
    copiamapa(&copia, &m);

    int i;
    int j;
    for (i=0 ; i< copia.linhas; i++){
        for (j=0; j< copia.colunas; j++){
            if (copia.mapa[i][j] == FANTASMA){

                int xdestino;
                int ydestino;

                int encontrou = paraondefantasmavai(i, j, &xdestino, &ydestino);

                if (encontrou){
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
            }
        }
    }
    libera_mapa(&copia);
}

int paraondefantasmavai (int xatual, int yatual,
                         int* xdestino, int*ydestino){

    int opcoes[4][2] = {
    {xatual,    yatual+1},
    {xatual+1,  yatual},
    {xatual,    yatual-1},
    {xatual-1,  yatual}
    };

    srand(time(0));

    int i;
    for (i=0; i<10 ; i++){

        int escolha = rand() % 4;

        if (pode_andar(&m, FANTASMA, opcoes[escolha][0],opcoes[escolha][1])){
            *xdestino = opcoes[escolha][0];
            *ydestino = opcoes[escolha][1];
            return 1;
        }
    }
    return 0;
}

void explodepilula (){

    if (!tempilula) return;

    explodepilula2(heroi.x, heroi.y, 0,1,3);
    explodepilula2(heroi.x, heroi.y, 0,-1,3);
    explodepilula2(heroi.x, heroi.y, 1,0,3);
    explodepilula2(heroi.x, heroi.y, -1,0,3);

    tempilula=0;
}

void explodepilula2 (int x, int y, int somax, int somay, int qtd){

    if (qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;

    if (!ehvalida(&m, novox, novoy)) return;
    if (ehparede(&m, novox, novoy)) return;

    m.mapa[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd - 1);
}

int main(){

    le_mapa(&m);
    encontra_no_mapa(&m, &heroi, HEROI);

    do{

        printf("Pilula: %s\n", (tempilula ? "SIM" : "NAO"));

        imprime_mapa(&m);

        printf("Qual seu comando? (a/w/s/d)\n");
        char comando;
        scanf(" %c",&comando); //espaço em branco para ENTER ser ignorado

        if (ehdirecao(comando))  move_pers(comando);
        if (comando == BOMBA)    explodepilula();

        fantasma();

    } while (!acabou());

    libera_mapa(&m);
    return 0;
}
