#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "calcdist.h"

void calcdist(MAP *p, POSICAO pos, int acl){
    int z = p->dist[pos.posX][pos.posY];
    if(z > acl && p->obj[pos.posX][pos.posY] == '.' && acl <= 20){
        p->dist[pos.posX][pos.posY] = acl; 
        
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                POSICAO newpos = {pos.posX+i, pos.posY+j};
                calcdist(p, newpos, acl+1);
            }    
        }
    }
}