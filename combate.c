#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "combate.h"

void ataqueini(INIMIGO *s, PLAYER *r, MAP mapa, int distrange){
    int X = s->pos.posX, Y = s->pos.posY;
    if (mapa.dist[X][Y] <= distrange){
        if (s->vidainimigo > 0  &&  ((rand()%21) + s->ataqueinimigo) >= r->defesa){
            r->vida -= s->danoinimigo;
        }
    }
}

void ataqueplayer(INIMIGO *s, PLAYER *r, MAP *mapa){
    if (s->vidainimigo > 0 && ((rand()%21) + r->ataqueespada) >= s->defesainimigo){
        s->vidainimigo -= ((2*(rand() % 4) + 2) + r->danoespada); 
        if(s->vidainimigo <= 0){
            mapa->isenemyhere[s->pos.posX][s->pos.posY] = 0;
        }
    }
}