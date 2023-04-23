#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarsaida.h"

void gerarsaida(POSICAO *saida,MAP *mapsaida ){
    int X, Y;
    X = rand() % COLS;
    Y = rand() % LINES;
    while ((mapsaida->obj[X][Y])=='#'){
        X = rand() % COLS;
        Y = rand() % LINES;
    }
    saida->posX = X;
    saida->posY = Y;
}