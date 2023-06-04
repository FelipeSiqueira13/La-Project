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

void ataqueplayerdistancia(INIMIGO *s, PLAYER *r, MAP *mapa){
    if (s->vidainimigo > 0 && r->flechas > 0 && s->trigger == 1 && ((rand()%21) + r->ataquearco) >= s->defesainimigo){
        s->vidainimigo -= ((2*(rand() % 6) + 2) + r->danoarco);
        if(s->vidainimigo <= 0){
            mapa->isenemyhere[s->pos.posX][s->pos.posY] = 0;
        }
    }
    if (r->flechas > 0){
        r->flechas -= 1;
    }
}

void ataqueaguabenta(INIMIGO *s, PLAYER *r, MAP *mapa){
    if (s->vidainimigo > 0 && r->aguabenta > 0 && s->trigger == 1){
        s->vidainimigo -= (4*(rand() % 8) + 4);
        if(s->vidainimigo <= 0){
            mapa->isenemyhere[s->pos.posX][s->pos.posY] = 0;
        }
    }
}