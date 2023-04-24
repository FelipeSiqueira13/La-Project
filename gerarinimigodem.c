#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarinimigodem.h"

void gerarinimigodem(INIMIGO *s, MAP *r){
    int X, Y;
    X = rand() % COLS;
    Y = rand() % LINES;
    while ((r->obj[X][Y])=='#'||(r->obj[X][Y])=='@'){
        X = rand() % COLS;
        Y = rand() % LINES;
    }
    s->inimigoX = X;
    s->inimigoY = Y;
    s->vidainimigo = 25;
    s->defesainimigo = 12;
    s->ataqueinimigo = 2;
    s->danoinimigo = 5;
    s->trigger = 0;
}