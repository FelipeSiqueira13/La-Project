#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>

#include "vision.h"

void vision(MAP *mapa, POSICAO pos){
    int i, x, y;
    double dir = 0;
    
    for(dir = 0; dir <= 2*3.14; dir += 0.05){
        for(i = 0; i < 20; i++){
            x = pos.posX + round(i*sin(dir));
            y = pos.posY + round(i*cos(dir));
            mapa->vision[x][y] = 2;
            if(mapa->obj[x][y] == '#') break;
        }
    }
}

void visionupdate(MAP *mapa, POSICAO max){
    int i, j;
    for(i = 0; i < max.posX; i++){
        for(j = 0; j < max.posY; j++){
            if(mapa->vision[i][j] == 2) mapa->vision[i][j] = 1;
        }   
    }
}