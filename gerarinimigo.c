#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarinimigo.h"

void gerarinimigodem(INIMIGO *s, MAP *r, PLAYER *t, POSICAO max){
    int X = rand() % max.posX, Y = rand() % max.posY;

    while ((r->obj[X][Y]) == '#' || ((X == t->pos.posX) && (Y == t->pos.posY))){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }

    s->pos.posX = X;
    s->pos.posY = Y;
    s->vidainimigo = 25;
    s->defesainimigo = 10;
    s->ataqueinimigo = 2;
    s->danoinimigo = ((rand() % 4) + 1 + 1);
    s->trigger = 0;
    s->lastnear = 0;
}

void gerarinimigofant(INIMIGO *s, MAP *r, PLAYER *t, POSICAO max){
    int X = rand() % max.posX, Y = rand() % max.posY;
    
    while ((r->obj[X][Y]) == '#' || ((X == t->pos.posX) && (Y == t->pos.posY))){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }

    s->pos.posX = X;
    s->pos.posY = Y;
    s->vidainimigo = 15;
    s->defesainimigo = 12;
    s->ataqueinimigo = 4;
    s->danoinimigo = ((2*(rand() % 4) + 1) + 3);
    s->trigger = 0;
    s->lastnear = 0;
}

void gerarinimigovam(INIMIGO *s, MAP *r, PLAYER *t, POSICAO max){
    int X = rand() % max.posX, Y = rand() % max.posY;

    while ((r->obj[X][Y]) == '#' || ((X == t->pos.posX) && (Y == t->pos.posY))){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }

    s->pos.posX = X;
    s->pos.posY = Y;
    s->vidainimigo = 50;
    s->defesainimigo = 8;
    s->ataqueinimigo = 4;
    s->danoinimigo = ((rand() % 4) + 1 + 3);
    s->trigger = 0;
    s->lastnear = 0;
}

void isactive(INIMIGO *s, MAP *r){
    if(r->vision[s->pos.posX][s->pos.posY] == 2) s->trigger = 1;
    else s->trigger = 0;
}