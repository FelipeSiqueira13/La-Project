#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerabau.h"

void gerabau(MAP *mapabau, POSICAO max){
    int X, Y;
    time_t t;
    srand48(time(&t));
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((mapabau->obj[X][Y])=='#'||(mapabau->obj[X][Y])=='@'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    mapabau->obj[X][Y] = 'M';
}