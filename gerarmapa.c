#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "gerarmapa.h"


void gerarmapa(int bauspawn,MAP *mapa, POSICAO max){
    MAP fakemapa;
    int i, j, k;

	for(i = 0; i<max.posX;i++){
		mapa->obj[i][0] = '#';
		mapa->obj[i][max.posY-1] = '#';
	}
	for(j = 1; j<max.posY;j++){
		mapa->obj[0][j] = '#';
		mapa->obj[max.posX-2][j] = '#';
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
}