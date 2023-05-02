#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarinimigofant.h"

void gerarinimigofant(INIMIGO *s, MAP *r, PLAYER *t, POSICAO max){
    int X, Y;
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((r->obj[X][Y]) == '#' || ((X == t->pos.posX) && (Y == t->pos.posY))){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    s->pos.posX = X;
    s->pos.posY = Y;
    s->vidainimigo = 15;
    s->defesainimigo = 15;
    s->ataqueinimigo = 4;
    s->danoinimigo = 3;
    s->trigger = 0;
}