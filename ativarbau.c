#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "ativarbau.h"


void ativarbau(PLAYER *s, MAP *posbau){
    int X;
    int Y;
    X = s->pos.posX;
    Y = s->pos.posY;
    if ('M' == posbau->obj[X][Y]){
        novositens(s);
        posbau->obj[X][Y] = '.';
    }
}