#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "player.h"
#include "map.h"
#include "bau.h"
#include "inimigo.h"
#include "posicao.h"
#include "gerarinimigo.h"
#include "movimento.h"
#include "calcdist.h"
#include "gerarmapa.h"
#include "vision.h"
#include "iniciarcontrol.h"
#include "gamecontrol.h"
#include "movimentoinimigo.h"
#include "combatemonstro.h"
#include "combateplayer.h"
#include "usarpocao.h"
#include "cards.h"


void update(PLAYER *st, MAP *mapa,POSICAO max) {
	int key = getch();	
	POSICAO pos = st->pos;

	switch(key) {
		case KEY_A1:
		case '7': 
			if(obstaculo(pos, mapa, -1, -1) == 0 && mapa->isenemyhere[st->pos.posX-1][st->pos.posY-1] == 0){
				st->pos = do_movement_action(pos, -1, -1, mapa);
				ativarbau(st,mapa);
			}
			break;
		
		case KEY_UP:
		case 'w':
		case 'W':
		case '8':
			if(obstaculo(pos, mapa, -1, +0) == 0 && mapa->isenemyhere[st->pos.posX-1][st->pos.posY] == 0){
				st->pos = do_movement_action(pos, -1, +0, mapa);
				ativarbau(st,mapa); 
			}
			break;
		
		case KEY_A3:
		case '9':
			if(obstaculo(pos, mapa, -1, +1) == 0 && mapa->isenemyhere[st->pos.posX-1][st->pos.posY+1] == 0){
				st->pos = do_movement_action(pos, -1, +1, mapa); 
				ativarbau(st,mapa);
			}
			break;

		case KEY_LEFT:
		case 'a':
		case 'A':
		case '4': 
			if(obstaculo(pos, mapa, +0, -1) == 0 && mapa->isenemyhere[st->pos.posX][st->pos.posY-1] == 0){
				st->pos = do_movement_action(pos, +0, -1, mapa); 
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
			if(obstaculo(pos, mapa, +0, +1) == 0 && mapa->isenemyhere[st->pos.posX][st->pos.posY+1] == 0){
				st->pos = do_movement_action(pos,+0, +1, mapa); 
				ativarbau(st,mapa);
			}
			break;
		
		case KEY_C1:
		case '1': 
			if(obstaculo(pos, mapa, +1, -1) == 0 && mapa->isenemyhere[st->pos.posX+1][st->pos.posY-1] == 0){
				st->pos = do_movement_action(pos, +1, -1, mapa); 
				ativarbau(st,mapa);
			}
			break;

		case KEY_DOWN:
		case 's':
		case 'S':
		case '2': 
			if(obstaculo(pos, mapa, +1, +0) == 0 && mapa->isenemyhere[st->pos.posX+1][st->pos.posY] == 0){
				st->pos = do_movement_action(pos, +1, +0, mapa); 
				ativarbau(st,mapa);
			}
			break;

		case KEY_C3:
		case '3': 
			if(obstaculo(pos, mapa, +1, +1) == 0 && mapa->isenemyhere[st->pos.posX+1][st->pos.posY+1] == 0){
				st->pos = do_movement_action(pos, +1, +1, mapa); 
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
		case 'z':
			st->ataquepronto = 1;
			break;

		case 'c':
			st->pocaopronta = 1;
			break;
		case 'p':
			for(int i = 0; i< max.posX ;i++){
				for(int j = 0; j<max.posY;j++){
					if((mapa->obj[i][j] == 'S')){
						mvaddch(i, j, mapa->obj[i][j] | A_BOLD);
					}
				}
			}
			break;
		
	}
}

int main() {
	CONTROL gamecontroller; 
	PLAYER st;
	INIMIGO inidem[100],inifnt [100];
	CARDS cards;
	startcards(&cards);
	int i = 0, j = 0;
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
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);

	POSICAO max = {nrows-1, ncols-1};

	MAP mapa;

	iniciarcontrol(&gamecontroller);

	gerarmapa(gamecontroller.bauspawn,&mapa,&st, max);

	gerar(&st);

	for(i = 0;i < gamecontroller.qntdem;i++){
		gerarinimigodem(&inidem[i],&mapa,&st, max);
	}

	for(i = 0;i < gamecontroller.qntfnt;i++){
		gerarinimigofant(&inifnt[i],&mapa,&st, max);
	}

	while(1) {
		if(ativarsaida(&gamecontroller,&st, &mapa, max) ==1){
			wclear(wnd);
			callACard(&st, &gamecontroller,cards);
			
			for(i = 0;i < gamecontroller.qntdem;i++){
				gerarinimigodem(&inidem[i],&mapa,&st, max);
			}

			for(i = 0;i < gamecontroller.qntfnt;i++){
				gerarinimigofant(&inifnt[i],&mapa,&st, max);
			}
			wclear(wnd);
		}
		wclear(wnd);
		move(nrows - 1, 0);
		for(i = 0; i<LINES-1;i++){
			for(j = 0; j<COLS;j++){
				mapa.dist[i][j]=21;
			}
		}
		calcdist(&mapa,st.pos,0);
		visionupdate(&mapa,max);
		vision(&mapa,st.pos);
		attron(COLOR_PAIR(COLOR_BLUE));
		int nivel = st.nivel;
		if (nivel>=3){
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d Agua Benta:%d Vida dos Inimigos:", st.pos.posY, st.pos.posX, nrows, ncols, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
			for (i = 0; i < gamecontroller.qntdem; i++){
				int iniX = inidem[i].pos.posX;
				int iniY = inidem[i].pos.posY;
				if (mapa.dist[iniX][iniY] <= 3){
					printw(" %d", inidem[i].vidainimigo);
				} 
			}

			for (i = 0; i < gamecontroller.qntfnt; i++){
				int ini2X = inifnt[i].pos.posX;
				int ini2Y = inifnt[i].pos.posY;
				if (mapa.dist[ini2X][ini2Y] <= 3){
					printw(" %d", inifnt[i].vidainimigo);
				}
			}
		} else{
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d ???:%d Vida dos Inimigos:", st.pos.posY, st.pos.posX, nrows, ncols, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
			for (i = 0; i < gamecontroller.qntdem; i++){
				int iniX = inidem[i].pos.posX;
				int iniY = inidem[i].pos.posY;
				if (mapa.dist[iniX][iniY] <= 3 && inidem[i].vidainimigo > 0){
					printw(" %d", inidem[i].vidainimigo);
				} 
			}

			for (i = 0; i < gamecontroller.qntfnt; i++){
				int ini2X = inifnt[i].pos.posX;
				int ini2Y = inifnt[i].pos.posY;
				if (mapa.dist[ini2X][ini2Y] <= 3 && inifnt[i].vidainimigo > 0){
					printw(" %d", inifnt[i].vidainimigo);
				}
			}
		}
		attroff(COLOR_PAIR(COLOR_BLUE));

		attron(COLOR_PAIR(COLOR_YELLOW));
		if(st.debugmode==0){
			for(i = 0; i<LINES-1;i++){
				for(j = 0; j<COLS;j++){
					if((mapa.vision[i][j] == 2)){
						if(mapa.obj[i][j] == 'S'){
						attroff(COLOR_PAIR(COLOR_YELLOW));
						attron(COLOR_PAIR(COLOR_GREEN));
						mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
						attroff(COLOR_PAIR(COLOR_GREEN));
						attron(COLOR_PAIR(COLOR_YELLOW));
					}else mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
					}else if(mapa.vision[i][j] == 1){
						if(mapa.obj[i][j] == 'S'){
						attroff(COLOR_PAIR(COLOR_YELLOW));
						attron(COLOR_PAIR(COLOR_GREEN));
						mvaddch(i, j, mapa.obj[i][j]);
						attroff(COLOR_PAIR(COLOR_GREEN));
						attron(COLOR_PAIR(COLOR_YELLOW));
					}else mvaddch(i, j, mapa.obj[i][j]);
					}
				}
			}
		}else{
			for(i = 0; i<LINES-1;i++){
				for(j = 0; j<COLS;j++){
					mvaddch(i, j, (47+mapa.dist[i][j]) | A_BOLD);
				}
			}
		}
		mvaddch(st.pos.posX, st.pos.posY, '@' | A_BOLD);
		
		attroff(COLOR_PAIR(COLOR_YELLOW));
		for(i=0;i<gamecontroller.qntdem;i++)isactive(&inidem[i],&mapa);
		for(i=0;i<gamecontroller.qntfnt;i++)isactive(&inifnt[i],&mapa);
		attron(COLOR_PAIR(COLOR_RED));
		for(i = 0;i < gamecontroller.qntdem;i++){
			if(inidem[i].trigger==1 && inidem[i].vidainimigo > 0)
				mvaddch(inidem[i].pos.posX,inidem[i].pos.posY , 'D' | A_BOLD);
		}
		for(i = 0;i < gamecontroller.qntfnt;i++){
			if(inifnt[i].trigger==1 && inifnt[i].vidainimigo > 0)
				mvaddch(inifnt[i].pos.posX,inifnt[i].pos.posY , 'F' | A_BOLD);
		}
		attroff(COLOR_PAIR(COLOR_RED));
		move(st.pos.posX, st.pos.posY);	
		update(&st, &mapa,max);

		for(i = 0;i < gamecontroller.qntdem;i++){
			if(inidem[i].trigger==1)
				movimento_do_inimigo_dem(/*&st,*/ &inidem[i], &mapa);
		}
		for(i = 0;i < gamecontroller.qntfnt;i++){
			if(inifnt[i].trigger==1)
				movimento_do_inimigo_fant(/*&st,*/ &inifnt[i], &mapa);
		}
		for (i = 0; i < gamecontroller.qntdem; i++){
			int X = inidem[i].pos.posX;
    		int Y = inidem[i].pos.posY;
    		if (mapa.dist[X][Y] <= 1 && st.ataquepronto == 1 && inidem[i].vidainimigo>0){
				ataqueplayer(&inidem[i], &st);
				st.ataquepronto = 0;
			}
			ataqueini(&inidem[i], &st, mapa, 2);
		}

		for (i = 0; i < gamecontroller.qntfnt; i++){
			int X = inifnt[i].pos.posX;
    		int Y = inifnt[i].pos.posY;
    		if (mapa.dist[X][Y] <= 1 && st.ataquepronto == 1 && inidem[i].vidainimigo>0){
				ataqueplayer(&inifnt[i], &st);
				st.ataquepronto = 0;
			}
			ataqueini(&inifnt[i], &st, mapa, 1);
		}

		if ((st.pocaopronta == 1) && (st.vida < st.vidamaxima) && st.vida > 0){
			usarpocao(&st);
			st.pocaopronta = 0;

		}

		for(i = 0;i < gamecontroller.qntdem;i++){
			if(inidem[i].trigger==1)
				mvaddch(inidem[i].pos.posX,inidem[i].pos.posY , 'D' | A_BOLD);
		}
		for(i = 0;i < gamecontroller.qntfnt;i++){
			if(inifnt[i].trigger==1)
				mvaddch(inifnt[i].pos.posX,inifnt[i].pos.posY , 'F' | A_BOLD);
		}

	}

	return 0;
}

