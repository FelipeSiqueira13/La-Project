#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "movimentoinimigo.h"

void movimento_do_inimigo(INIMIGO *s, MAP *r){
    POSICAO posini = s->pos, newposini = {1, 1};
    int dist = 20, i, j;
    
    if(r->dist[s->pos.posX][s->pos.posY] == 1){}
    else{
        if (s->trigger == 1 && s->vidainimigo > 0){
            for(i = -1; i <= 1; i++){
                for(j = -1; j <= 1; j++){
                    if(r->dist[s->pos.posX+i][s->pos.posY+j] < dist  &&  r->isenemyhere[s->pos.posX+i][s->pos.posY+j] == 0){
                        newposini.posX = i;
                        newposini.posY = j;
                        dist = r->dist[s->pos.posX+i][s->pos.posY+j];
                    }
                    else{
                        if((r->dist[s->pos.posX+i][s->pos.posY+j] == dist)  &&  (j == 0 || i == 0)  &&  r->isenemyhere[s->pos.posX+i][s->pos.posY+j] == 0){
                            newposini.posX = i;
                            newposini.posY = j;
                        }
                    }
                }
            }
            s->pos = do_movement_action(posini, newposini.posX, newposini.posY, r);
        }
    } 
}