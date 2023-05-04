#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerabau.h"

void gerabau(MAP *mapabau, POSICAO max){
    int X = rand() % max.posX, Y = rand() % max.posY;
    time_t t;
    srand48(time(&t));
    
    while ((mapabau->obj[X][Y])=='#'||(mapabau->obj[X][Y])=='@'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    mapabau->obj[X][Y] = 'M';
}