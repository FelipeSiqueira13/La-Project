#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "calcdist.h"

void calcdist(MAP *p,POSICAO pos, int acl){
    int z = p->dist[pos.posX][pos.posY];
    if(z > acl && p->obj[pos.posX][pos.posY] == '.' && acl <= 15){
        p->dist[pos.posX][pos.posY] = acl; 

        int i=0,j=0;
        
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                POSICAO newpos = {pos.posX+i, pos.posY+j};
                calcdist(p,newpos,acl+1);
            }    
        }
    }

}