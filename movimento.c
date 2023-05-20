#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "movimento.h"

POSICAO do_movement_action(POSICAO st, int dx, int dy, MAP *mapa) {
	mapa->isenemyhere[st.posX][st.posY] = 0;
	st.posX += dx;
	st.posY += dy;
	mapa->isenemyhere[st.posX][st.posY] = 1;
	return st;
}

int obstaculo(POSICAO pos, MAP *mapa, int dx, int dy){
	int o = 1;
	if(dx != dy  &&  (dx == 0 || dy == 0)){
		if(mapa->obj[pos.posX+dx][pos.posY+dy] != '#') o = 0; 
	}
	else{
		if((mapa->obj[pos.posX+dx][pos.posY+dy] != '#'  &&  mapa->obj[pos.posX+dx][pos.posY] != '#') || (mapa->obj[pos.posX+dx][pos.posY+dy] != '#' && mapa->obj[pos.posX][pos.posY+dy] != '#')) o = 0;
	}
	return o;
}
