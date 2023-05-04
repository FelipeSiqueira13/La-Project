#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "obstaculo.h"

int obstaculo(POSICAO pos, MAP *mapa, int dx, int dy){
	int o = 1;
	if(dx != dy && (dx == 0 || dy == 0)){
		if(mapa->obj[pos.posX+dx][pos.posY+dy] != '#') o = 0; 
	}
	else{
		if((mapa->obj[pos.posX+dx][pos.posY+dy] != '#' && mapa->obj[pos.posX+dx][pos.posY] != '#') || (mapa->obj[pos.posX+dx][pos.posY+dy] != '#' && mapa->obj[pos.posX][pos.posY+dy] != '#')) o = 0;
	}
	return o;
}