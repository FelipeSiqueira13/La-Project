#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarmapa.h"


void gerarmapa(int bauspawn,MAP *mapa, PLAYER *st, POSICAO max){
    MAP fakemapa;
    int i, j, k;

	for(i = 0; i<max.posX;i++){
		mapa->obj[i][0] = '#';
		mapa->obj[i][max.posY-1] = '#';
		mapa->vision[i][0] = 0;
		mapa->vision[i][max.posY-1] = 0;
		mapa->isenemyhere[i][0] = 0;
		mapa->isenemyhere[i][max.posY-1] = 0;
	}
	for(j = 1; j<max.posY;j++){
		mapa->obj[0][j] = '#';
		mapa->obj[max.posX-2][j] = '#';
		mapa->vision[0][j] = 0;
		mapa->vision[max.posX-2][j] = 0;
		mapa->isenemyhere[0][j] = 0;
		mapa->isenemyhere[max.posX-2][j] = 0;
	}
	for(i = 1; i<max.posX-2;i++){
		for(j = 1; j<max.posY-1;j++){
			mapa->vision[i][j] = 0;
			if( rand() % 100 > 40){
			mapa->obj[i][j] = '.';
			}else mapa->obj[i][j] = '#';
		}
	}
	fakemapa = *mapa;

	int cont, cont2;
	for(k=0;k < 4; k++){
		for(i = 2; i<max.posX-2;i++){
			for(j = 2; j<max.posY-1;j++){
				cont = 0;
				cont2 = 0;
				if(mapa->obj[i+1][j] == '#') cont++;
				if(mapa->obj[i+1][j-1] == '#') cont++;
				if(mapa->obj[i+1][j+1] == '#') cont++;
				if(mapa->obj[i][j] == '#') cont++;
				if(mapa->obj[i][j-1] == '#') cont++;
				if(mapa->obj[i][j+1] == '#') cont++;
				if(mapa->obj[i-1][j] == '#') cont++;
				if(mapa->obj[i-1][j-1] == '#') cont++;
				if(mapa->obj[i-1][j+1] == '#') cont++;
				
				if(mapa->obj[i+2][j+2] == '#') cont2++;
				if(mapa->obj[i+2][j-2] == '#') cont2++;
				if(mapa->obj[i+2][j+1] == '#') cont2++;
				if(mapa->obj[i+2][j-1] == '#') cont2++;
				if(mapa->obj[i+2][j] == '#') cont2++;
				if(mapa->obj[i-2][j+2] == '#') cont2++;
				if(mapa->obj[i-2][j-2] == '#') cont2++;
				if(mapa->obj[i-2][j+1] == '#') cont2++;
				if(mapa->obj[i-2][j-1] == '#') cont2++;
				if(mapa->obj[i-2][j] == '#') cont2++;
				if(mapa->obj[i-1][j-2] == '#') cont2++;
				if(mapa->obj[i-1][j+2] == '#') cont2++;
				if(mapa->obj[i][j-2] == '#') cont2++;
				if(mapa->obj[i][j+2] == '#') cont2++;
				if(mapa->obj[i+1][j-2] == '#') cont2++;
				if(mapa->obj[i+1][j+2] == '#') cont2++;
				
				if(cont >= 5 || cont2 <= 2){
					fakemapa.obj[i][j] = '#';
				}else{
					fakemapa.obj[i][j] = '.';
				}
			}
		}
		*mapa = fakemapa;
	}

	for(k=0;k < 3; k++){
		for(i = 2; i<max.posX-2;i++){
			for(j = 2; j<max.posY-1;j++){
				cont = 0;
				if(mapa->obj[i+1][j] == '#') cont++;
				if(mapa->obj[i+1][j-1] == '#') cont++;
				if(mapa->obj[i+1][j+1] == '#') cont++;
				if(mapa->obj[i][j] == '#') cont++;
				if(mapa->obj[i][j-1] == '#') cont++;
				if(mapa->obj[i][j+1] == '#') cont++;
				if(mapa->obj[i-1][j] == '#') cont++;
				if(mapa->obj[i-1][j-1] == '#') cont++;
				if(mapa->obj[i-1][j+1] == '#') cont++;

				if(cont >= 5){
					
				}else{
					fakemapa.obj[i][j] = '.';
				}

			}
		}
		*mapa = fakemapa;
	}	
	gerarsaida(mapa, max);

	for(i = 0;i < bauspawn;i++){
		gerabau(mapa, max);
	}
	gerarplayer(mapa,st,max);
}

void gerarplayer(MAP *mapa,PLAYER *st,POSICAO max){
	int X, Y;
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((mapa->obj[X][Y]) == '#'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    st->pos.posX = X;
    st->pos.posY = Y;
}

void gerarsaida(MAP *mapsaida, POSICAO max){
    int X, Y;
    X = rand() % max.posX;
    Y = rand() % max.posY;
    while ((mapsaida->obj[X][Y])=='#'){
        X = rand() % max.posX;
        Y = rand() % max.posY;
    }
    mapsaida->obj[X][Y]='S';
}

int ativarsaida(CONTROL *gamecontroller,PLAYER *s,MAP *mapsaida, POSICAO max){
    int X,Y, ret = 0;
    X = s->pos.posX;
    Y = s->pos.posY;

    if ('S' == mapsaida->obj[X][Y]){
		gamecontroller->qntdem += rand() % 9;
		gamecontroller->qntfnt += rand() % 5;
		gamecontroller->qntvmp += rand() % 4;
        gerarmapa(gamecontroller->bauspawn,mapsaida,s, max);
        ret = 1;
    }
    return ret;
}

void gerar(PLAYER *s) {
	s->debugmode = 0;
	s->nivel = 1;
	s->vida = 100;
	s->vidamaxima = 100;
	s->defesa = 14;
	s->flechas = 5;
	s->ataqueespada = 1;
	s->danoespada = 2;
	s->ataquearco = 1;
	s->pocoesvida = 1;
	s->aguabenta = 0;
	s->ataquepronto = 0;
	s->pocaopronta = 0;
}