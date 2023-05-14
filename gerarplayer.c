#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarplayer.h"


void gerarplayer(MAP *mapa,PLAYER *st,POSICAO max){
	int X, Y;
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((mapa->obj[X][Y]) == '#'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    st->pos.posX = X;
    st->pos.posY = Y;
}