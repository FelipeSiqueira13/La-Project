#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarsaida.h"

void gerarsaida(MAP *mapsaida, POSICAO max){
    int X, Y;
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((mapsaida->obj[X][Y]) == '#'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    mapsaida->obj[X][Y] = 'S';
}