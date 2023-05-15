#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "combatemonstro.h"

void ataqueini(INIMIGO *s, PLAYER *r, MAP mapa, int distrange){
    int X = s->pos.posX;
    int Y = s->pos.posY;
    if (mapa.dist[X][Y] <= distrange){
        if (s->vidainimigo > 0 && ((rand()%21) + s->ataqueinimigo) >= r->defesa){
            r->vida -= s->danoinimigo;
        }
    }
}

