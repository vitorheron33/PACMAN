#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

void move_pers(char comando);
int ehdirecao (char comando);
void fantasma();
int paraondefantasmavai (int xatual, int yatual,
                         int* xdestino, int*ydestino);
void explodepilula();
void explodepilula2 (int x, int y, int somax, int somay, int qtd);
int acabou();
