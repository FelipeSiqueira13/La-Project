#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarsaida.h"

void gerarsaida(POSICAO *saida,MAP *mapsaida, POSICAO max){
    int X, Y;
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((mapsaida->obj[X][Y])=='#'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    saida->posX = X;
    saida->posY = Y;
}