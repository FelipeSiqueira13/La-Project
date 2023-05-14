#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mudarmapa.h"


int ativarsaida(int bauspawn,PLAYER *s,MAP *mapsaida, POSICAO max){
    int X,Y, ret = 0;
    X = s->pos.posX;
    Y = s->pos.posY;
    if ('S' == mapsaida->obj[X][Y]){
        gerarmapa(bauspawn,mapsaida,s, max);
        ret = 1;
    }
    return ret;
}
// se estiver em cima de uma saída usar a função em gerarmapa.h para gerar um novo mapa