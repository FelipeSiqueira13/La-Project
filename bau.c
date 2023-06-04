#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "bau.h"

void novositens(PLAYER *s){
    int nivel = s->nivel;
    if (nivel >= 5){
        s->aguabenta += rand() % 2;
        s->flechas += rand() % 41;
        s->pocoesvida += rand() % 5;
    } else {
        s->flechas += rand() % 21;
        s->pocoesvida += rand() % 3;
    }
}

void gerabau(MAP *mapabau, POSICAO max){
    int X = rand() % max.posX, Y = rand() % max.posY;
    time_t t;
    srand48(time(&t));
    
    while ((mapabau->obj[X][Y]) == '#'  ||  (mapabau->obj[X][Y]) == '@'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    mapabau->obj[X][Y] = 'M';
}

void ativarbau(PLAYER *s, MAP *posbau){
    int X = s->pos.posX, Y = s->pos.posY;
    if ('M' == posbau->obj[X][Y]){
        novositens(s);
        posbau->obj[X][Y] = '.';
    }
}