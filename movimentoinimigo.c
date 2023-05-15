#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "movimentoinimigo.h"

void movimento_do_inimigo_dem(PLAYER *st, INIMIGO *s, MAP *r){
    POSICAO posini = s->pos;
    POSICAO newposini;
    int dist = 20;

    if (s->trigger == 1 && s->vidainimigo != 0) {
        if(r->dist[s->pos.posX][s->pos.posY] < dist) dist = r->dist[s->pos.posX][s->pos.posY];
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(r->dist[s->pos.posX+i][s->pos.posY+j] < dist && r->isenemyhere[s->pos.posX][s->pos.posY] == 0){
                    r->isenemyhere[s->pos.posX][s->pos.posY] = 0;
                    newposini.posX = s->pos.posX+i;
                    newposini.posY =  s->pos.posY+j;
                    dist = r->dist[s->pos.posX+i][s->pos.posY+j];
                    r->isenemyhere[s->pos.posX+i][s->pos.posY+j] = 1;
                }
            }
        }        
    }

    if(dist != 20){
        r->isenemyhere[s->pos.posX][s->pos.posY] = 0;
        if(st->pos.posX > s->pos.posX && st->pos.posY > s->pos.posY && obstaculo(posini, r, +1, +1) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +1, +1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX > s->pos.posX && st->pos.posY < s->pos.posY && obstaculo(posini, r, +1, -1) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +1, -1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX < s->pos.posX && st->pos.posY > s->pos.posY && obstaculo(posini, r, -1, +1) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, -1, +1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX < s->pos.posX && st->pos.posY < s->pos.posY && obstaculo(posini, r, -1, -1) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, -1, -1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX == s->pos.posX && st->pos.posY > s->pos.posY && obstaculo(posini, r, +0, +1) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +0, +1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX > s->pos.posX && st->pos.posY == s->pos.posY && obstaculo(posini, r, +1, +0) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +1, +0);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX == s->pos.posX && st->pos.posY < s->pos.posY && obstaculo(posini, r, +0, -1) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +0, -1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX < s->pos.posX && st->pos.posY == s->pos.posY && obstaculo(posini, r, -1, +0) == 0 && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, -1, +0);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }        
    }
}


void movimento_do_inimigo_fant(PLAYER *st, INIMIGO *s, MAP *r){
    POSICAO posini = s->pos;
    POSICAO newposini;
    int dist = 20;

    if (s->trigger == 1 && s->vidainimigo != 0) {
        if(r->dist[s->pos.posX][s->pos.posY] < dist) dist = r->dist[s->pos.posX][s->pos.posY];
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(r->dist[s->pos.posX+i][s->pos.posY+j] < dist){
                    r->isenemyhere[s->pos.posX][s->pos.posY] = 0;
                    newposini.posX = s->pos.posX+i;
                    newposini.posY =  s->pos.posY+j;
                    dist = r->dist[s->pos.posX+i][s->pos.posY+j];
                    r->isenemyhere[s->pos.posX+i][s->pos.posY+j] = 1;
                }
            }
        }        
    }

    if(dist != 20){
        r->isenemyhere[s->pos.posX][s->pos.posY] = 0;
        if(st->pos.posX > s->pos.posX && st->pos.posY > s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +1, +1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX > s->pos.posX && st->pos.posY < s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +1, -1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX < s->pos.posX && st->pos.posY > s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, -1, +1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX < s->pos.posX && st->pos.posY < s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, -1, -1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX == s->pos.posX && st->pos.posY > s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +0, +1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX > s->pos.posX && st->pos.posY == s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +1, +0);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX == s->pos.posX && st->pos.posY < s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, +0, -1);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }
        if(st->pos.posX < s->pos.posX && st->pos.posY == s->pos.posY && r->isenemyhere[ s->pos.posX][s->pos.posY] == 0){
            s->pos = do_movement_action(posini, -1, +0);
            r->isenemyhere[s->pos.posX][s->pos.posY] = 1;
        }        
    }
}

