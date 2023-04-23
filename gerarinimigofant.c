#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarinimigofant.h"

void gerarinimigodem(INIMIGO *s, MAP *r, PLAYER *t){
    int X, Y;
    X = rand() % COLS;
    Y = rand() % LINES;
    while ((r->obj[X][Y]) == '#' || ((X == t->pos.posX) && (Y == t->pos.posY))){
        X = rand() % COLS;
        Y = rand() % LINES;
    }
    s->pos.posX = X;
    s->pos.posY = Y;
    s->vidainimigo = 15;
    s->defesainimigo = 15;
    s->ataqueinimigo = 4;
    s->danoinimigo = 3;
    s->trigger = 0;
}