#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"
#include "player.h"
#include "map.h"
#include "bau.h"
#include "inimigo.h"
#include "posicao.h"
#include "gerabau.h"
#include "gerarinimigodem.h"
#include "movimento.h"
#include "obstaculo.h"
#include "gerarsaida.h"
#include "calcdist.h"
#include "ativarbau.h"
#include "gerarinimigofant.h"
#include "gerarmapa.h"


void update(PLAYER *st, MAP *mapa) {
	int key = getch();	
	POSICAO pos = st->pos;

	switch(key) {
		case KEY_A1:
		case '7': 
			if(obstaculo(pos, mapa, -1, -1) == 0){
				st->pos = do_movement_action(pos, -1, -1);
				ativarbau(st,mapa);
			}
			break;
		
		case KEY_UP:
		case 'w':
		case 'W':
		case '8':
			if(obstaculo(pos, mapa, -1, +0) == 0){
				st->pos = do_movement_action(pos, -1, +0);
				ativarbau(st,mapa); 
			}
			break;
		
		case KEY_A3:
		case '9':
			if(obstaculo(pos, mapa, -1, +1) == 0){
				st->pos = do_movement_action(pos, -1, +1); 
				ativarbau(st,mapa);
			}
			break;

		case KEY_LEFT:
		case 'a':
		case 'A':
		case '4': 
			if(obstaculo(pos, mapa, +0, -1) == 0){
				st->pos = do_movement_action(pos, +0, -1); 
				ativarbau(st,mapa);
			}
			break;
		
		case KEY_B2:
		case '5': 
			break;
		
		case KEY_RIGHT:
		case 'd':
		case 'D':
		case '6': 
			if(obstaculo(pos, mapa, +0, +1) == 0){
				st->pos = do_movement_action(pos,+0, +1); 
				ativarbau(st,mapa);
			}
			break;
		
		case KEY_C1:
		case '1': 
			if(obstaculo(pos, mapa, +1, -1) == 0){
				st->pos = do_movement_action(pos, +1, -1); 
				ativarbau(st,mapa);
			}
			break;

		case KEY_DOWN:
		case 's':
		case 'S':
		case '2': 
			if(obstaculo(pos, mapa, +1, +0) == 0){
				st->pos = do_movement_action(pos, +1, +0); 
				ativarbau(st,mapa);
			}
			break;

		case KEY_C3:
		case '3': 
			if(obstaculo(pos, mapa, +1, +1) == 0){
				st->pos = do_movement_action(pos, +1, +1); 
				ativarbau(st,mapa);
			}
			break;
			
		case 'Q':
		case 'q': 
			endwin(); exit(0); 
			break;

		case 'm':
			novositens(st);
			break;

		case 'n':
			if(st->debugmode == 0){
				st->debugmode = 1;
			}else{
				st->debugmode = 0;
			}
			break;
	}
}

int main() {
	PLAYER st;
	INIMIGO ini[100];
	INIMIGO ini2 [100];
	POSICAO saida;
	int i = 0, j = 0, inispawn = 10, bauspawn = 3, inispawn2 = 7;
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);

	srand(time(NULL));
	start_color();

	cbreak();
	noecho();	//nao pegar inputs repetidamente
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);	//pega informacoes do teclado

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	
	POSICAO max = {nrows, ncols};

	gerar(&st);

	MAP mapa;

	gerarmapa(&mapa, max);
	
	for(i = 0;i < bauspawn;i++){
		gerabau(&mapa, max);
	}

	for(i = 0;i < inispawn;i++){
		gerarinimigodem(&ini[i],&mapa,&st, max);
	}

	for(i = 0;i < inispawn2;i++){
		gerarinimigofant(&ini2[i],&mapa,&st, max);
	}

	gerarsaida(&saida,&mapa, max);

	while(1) {
		move(nrows - 1, 0);
		for(i = 0; i<LINES-1;i++){
			for(j = 0; j<COLS;j++){
				mapa.dist[i][j]=16;
			}
		}
		calcdist(&mapa,st.pos,0);
		attron(COLOR_PAIR(COLOR_BLUE));
		int nivel = st.nivel;
		if (nivel>=5){
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d Agua Benta:%d", st.pos.posX, st.pos.posY, ncols, nrows, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
		} else{
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d ???:%d", st.pos.posX, st.pos.posY, ncols, nrows, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
		}
		attroff(COLOR_PAIR(COLOR_BLUE));

		attron(COLOR_PAIR(COLOR_YELLOW));
		if(st.debugmode==0){
			for(i = 0; i<LINES-1;i++){
				for(j = 0; j<COLS;j++){
					if((i == st.pos.posX) && (j == st.pos.posY)){
						mvaddch(i, j, '@' | A_BOLD);
					}else mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
				}
			}
		}else{
			for(i = 0; i<LINES-1;i++){
				for(j = 0; j<COLS;j++){
					if((i == st.pos.posX) && (j == st.pos.posY)){
						mvaddch(i, j, '@' | A_BOLD);
					}else mvaddch(i, j, (47+mapa.dist[i][j]) | A_BOLD);
				}
			}
		}calcdist(&mapa,st.pos,0);
		attroff(COLOR_PAIR(COLOR_YELLOW));
		attron(COLOR_PAIR(COLOR_RED));
		for(i = 0;i < inispawn;i++){
			mvaddch(ini[i].pos.posX,ini[i].pos.posY , 'D' | A_BOLD);
		}
		for(i = 0;i < inispawn2;i++){
			mvaddch(ini2[i].pos.posX,ini2[i].pos.posY , 'F' | A_BOLD);
		}
		mvaddch(saida.posX,saida.posY, 'S' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_RED));
		move(st.pos.posX, st.pos.posY);	
		update(&st, &mapa);
	}

	return 0;
}

