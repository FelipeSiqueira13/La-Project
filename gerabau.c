#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerabau.h"

void gerabau(POSICAO *bau,MAP *mapabau){
    int X, Y;
    time_t t;
    srand48(time(&t));
    X = rand() % COLS;
    Y = rand() % LINES;
    while ((mapabau->obj[X][Y])=='#'||(mapabau->obj[X][Y])=='@'){
        X = rand() % COLS;
        Y = rand() % LINES;
    }
    bau->posX = X;
    bau->posY = Y;
}