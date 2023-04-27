#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarinimigodem.h"

void gerarinimigodem(INIMIGO *s, MAP *r, PLAYER *t, POSICAO max){
    int X = rand() % max.posX, Y = rand() % max.posY;

    while ((r->obj[X][Y]) == '#' || ((X == t->pos.posX) && (Y == t->pos.posY))){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    
    s->pos.posX = X;
    s->pos.posY = Y;
    s->vidainimigo = 25;
    s->defesainimigo = 12;
    s->ataqueinimigo = 2;
    s->danoinimigo = 5;
    s->trigger = 0;
}
void isactive(INIMIGO *s, MAP *r){
    if(r->vision[s->pos.posX][s->pos.posY] == 2) s->trigger = 1;
    else s->trigger = 0;
}