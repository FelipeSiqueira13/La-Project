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
#include "gamecontrol.h"
#include "movimentoinimigo.h"
#include "combate.h"
#include "usarpocao.h"
#include "cards.h"


void update(PLAYER *st, MAP *mapa,CONTROL *gamecontroller,POSICAO max) {
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
		case 'Z':
			st->ataquepronto = 1;
			break;

		case 'x':
		case 'X':
			st->ataquedistpronto = 1;
			break;

		case 'c':
		case 'C':
			st->pocaopronta = 1;
			break;

		case 'p':
		case 'P':
			for(int i = 0; i< max.posX ;i++){
				for(int j = 0; j<max.posY;j++){
					if((mapa->obj[i][j] == 'S')){
						mapa->vision[i][j] = 1;
					}
				}
			}
			break;

		case 'o':
		case 'O':
			gamecontroller->carinhos ++;
			break;
		
	}
}


int main() {
	CONTROL gamecontroller; 
	PLAYER st;
	INIMIGO inidem[100],inifnt [100], inivam[100];
	CARDS cards;
	startcards(&cards);
	WINDOW *wnd = initscr();
	int ncols, nrows,i,j;
	getmaxyx(wnd,nrows,ncols);

	srand(time(NULL));
	start_color();

	cbreak();
	noecho();	//nao pegar inputs repetidamente
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);	//pega informacoes do teclado


	init_color(8,415,156,0);
	init_pair(8,8,COLOR_BLACK);
	init_color(9,1000,400,700);
	init_pair(9,9,COLOR_BLACK);
	init_color(10,1000,0,0);
	init_color(11,0,1000,0);
	init_color(12,1000,1000,0);
	init_color(13,600,600,0);
	init_pair(11, 11, COLOR_BLACK);
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(12, 12, COLOR_BLACK);
    init_pair(13, 13, COLOR_BLACK);	
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, 10, COLOR_BLACK);
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);

	POSICAO max = {nrows, ncols};

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

	for(i = 0;i < gamecontroller.qntvam;i++){
		gerarinimigovam(&inivam[i],&mapa,&st, max);
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

			for(i = 0;i < gamecontroller.qntvam;i++){
				gerarinimigovam(&inivam[i],&mapa,&st, max);
			}

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
				if (mapa.dist[iniX][iniY] <= 10){
					printw(" %d", inidem[i].vidainimigo);
				} 
			}

			for (i = 0; i < gamecontroller.qntfnt; i++){
				int ini2X = inifnt[i].pos.posX;
				int ini2Y = inifnt[i].pos.posY;
				if (mapa.dist[ini2X][ini2Y] <= 10){
					printw(" %d", inifnt[i].vidainimigo);
				}
			}

			for (i = 0; i < gamecontroller.qntvam; i++){
				int iniX = inivam[i].pos.posX;
				int iniY = inivam[i].pos.posY;
				if (mapa.dist[iniX][iniY] <= 10){
					printw(" %d", inivam[i].vidainimigo);
				} 
			}
		} else{
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d ???:%d Vida dos Inimigos:", st.pos.posY, st.pos.posX, nrows, ncols, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
			for (i = 0; i < gamecontroller.qntdem; i++){
				int iniX = inidem[i].pos.posX;
				int iniY = inidem[i].pos.posY;
				if (mapa.dist[iniX][iniY] <= 10 && inidem[i].vidainimigo > 0){
					printw(" %d", inidem[i].vidainimigo);
				} 
			}

			for (i = 0; i < gamecontroller.qntfnt; i++){
				int ini2X = inifnt[i].pos.posX;
				int ini2Y = inifnt[i].pos.posY;
				if (mapa.dist[ini2X][ini2Y] <= 10 && inifnt[i].vidainimigo > 0){
					printw(" %d", inifnt[i].vidainimigo);
				}
			}

			for (i = 0; i < gamecontroller.qntvam; i++){
				int iniX = inivam[i].pos.posX;
				int iniY = inivam[i].pos.posY;
				if (mapa.dist[iniX][iniY] <= 10 && inivam[i].vidainimigo > 0){
					printw(" %d", inivam[i].vidainimigo);
				} 
			}
		}
		attroff(COLOR_PAIR(COLOR_BLUE));

		for(i = 0; i<LINES-1;i++){
			for(j = 0; j<COLS;j++){
				if((mapa.vision[i][j] == 2)){
					if(mapa.obj[i][j] == 'S'){
						attron(COLOR_PAIR(11));
						mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
						attroff(COLOR_PAIR(11));
					}else if(mapa.obj[i][j] == 'M'){
						attron(COLOR_PAIR(8));
						mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
						attroff(COLOR_PAIR(8));
					}else{
						attron(COLOR_PAIR(12));
						mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
						attroff(COLOR_PAIR(12));
					} 
				}else if(mapa.vision[i][j] == 1){
					if(mapa.obj[i][j] == 'S'){
						attron(COLOR_PAIR(11));
						mvaddch(i, j, mapa.obj[i][j]);
						attroff(COLOR_PAIR(11));
					}else if(mapa.obj[i][j] == 'M'){
						attron(COLOR_PAIR(8));
						mvaddch(i, j, mapa.obj[i][j]);
						attroff(COLOR_PAIR(8));
					}else{
						attron(COLOR_PAIR(13));
						mvaddch(i, j, mapa.obj[i][j]);
						attroff(COLOR_PAIR(13));
					} 
				}
			}
		}
		attron(COLOR_PAIR(9));
		mvaddch(st.pos.posX, st.pos.posY, '@' | A_BOLD);
		attroff(COLOR_PAIR(9));

		attron(COLOR_PAIR(10));
		for(i=0;i<gamecontroller.qntdem;i++)isactive(&inidem[i],&mapa);
		for(i=0;i<gamecontroller.qntfnt;i++)isactive(&inifnt[i],&mapa);
		for(i=0;i<gamecontroller.qntvam;i++)isactive(&inivam[i],&mapa);

		for(i = 0;i < gamecontroller.qntdem;i++){
			if(inidem[i].trigger==1 && inidem[i].vidainimigo > 0)
				mvaddch(inidem[i].pos.posX,inidem[i].pos.posY , 'D' | A_BOLD);
		}
		for(i = 0;i < gamecontroller.qntfnt;i++){
			if(inifnt[i].trigger==1 && inifnt[i].vidainimigo > 0)
				mvaddch(inifnt[i].pos.posX,inifnt[i].pos.posY , 'F' | A_BOLD);
		}

		for(i = 0;i < gamecontroller.qntvam;i++){
			if(inivam[i].trigger==1 && inivam[i].vidainimigo > 0)
				mvaddch(inivam[i].pos.posX,inivam[i].pos.posY , 'V' | A_BOLD);
		}

		attroff(COLOR_PAIR(10));
		move(st.pos.posX, st.pos.posY);	
		update(&st, &mapa, &gamecontroller,max);

		for(i = 0;i < gamecontroller.qntdem;i++){
			if(inidem[i].trigger==1)
				movimento_do_inimigo(&inidem[i], &mapa);
		}
		for(i = 0;i < gamecontroller.qntfnt;i++){
			if(inifnt[i].trigger==1)
				movimento_do_inimigo(&inifnt[i], &mapa);
		}
		for(i = 0;i < gamecontroller.qntvam;i++){
			if(inivam[i].trigger==1){
				movimento_do_inimigo(&inivam[i], &mapa);
				movimento_do_inimigo(&inivam[i], &mapa);
			}	
		}

		for (i = 0; i < gamecontroller.qntdem; i++){
			int X = inidem[i].pos.posX;
    		int Y = inidem[i].pos.posY;
    		if (mapa.dist[X][Y] <= 1 && st.ataquepronto == 1 && inidem[i].vidainimigo>0){
				ataqueplayer(&inidem[i], &st,&mapa);
				st.ataquepronto = 0;
			}
			ataqueini(&inidem[i], &st, mapa, 2);
		}
		for (i = 0; i < gamecontroller.qntfnt; i++){
			int X = inifnt[i].pos.posX;
    		int Y = inifnt[i].pos.posY;
    		if (mapa.dist[X][Y] <= 1 && st.ataquepronto == 1 && inifnt[i].vidainimigo>0){
				ataqueplayer(&inifnt[i], &st, &mapa);
				st.ataquepronto = 0;
			}
			ataqueini(&inifnt[i], &st, mapa, 1);
		}
		for (i = 0; i < gamecontroller.qntvam; i++){
			int X = inivam[i].pos.posX;
    		int Y = inivam[i].pos.posY;
    		if (mapa.dist[X][Y] <= 1 && st.ataquepronto == 1 && inivam[i].vidainimigo>0){
				ataqueplayer(&inivam[i], &st,&mapa);
				st.ataquepronto = 0;
			}
			ataqueini(&inivam[i], &st, mapa, 2);
		}

		for (i = 0; i < gamecontroller.qntdem; i++){
			int X = inidem[i].pos.posX;
    		int Y = inidem[i].pos.posY;
    		if (mapa.dist[X][Y] > 1 && mapa.dist[X][Y] <= 10 && st.ataquedistpronto == 1 && inidem[i].vidainimigo>0){
				ataqueplayerdistancia(&inidem[i], &st,&mapa);
				st.ataquedistpronto = 0;
			}
		}
		for (i = 0; i < gamecontroller.qntfnt; i++){
			int X = inifnt[i].pos.posX;
    		int Y = inifnt[i].pos.posY;
    		if (mapa.dist[X][Y] > 1 && mapa.dist[X][Y] <= 10 && st.ataquedistpronto == 1 && inidem[i].vidainimigo>0){
				ataqueplayerdistancia(&inifnt[i], &st,&mapa);
				st.ataquedistpronto = 0;
			}
		}
		for (i = 0; i < gamecontroller.qntvam; i++){
			int X = inivam[i].pos.posX;
    		int Y = inivam[i].pos.posY;
    		if (mapa.dist[X][Y] > 1 && mapa.dist[X][Y] <= 10 && st.ataquedistpronto == 1 && inidem[i].vidainimigo>0){
				ataqueplayerdistancia(&inivam[i], &st,&mapa);
				st.ataquedistpronto = 0;
			}
		}

		if ((st.pocaopronta == 1) && (st.vida < st.vidamaxima) && st.vida > 0){
			usarpocao(&st);
			st.pocaopronta = 0;

		}


		if(st.vida < 0 && st.debugmode == 1){
			    wclear(wnd);
    			printw("\n\n\n\n\n\n\n\t\t YOU ARE DEAD, NOT A BIG SURPRISE\n\t\t press any key to quit");
				getch();
				endwin(); exit(0); 
		}
		if(gamecontroller.carinhos > 9){
				wclear(wnd);
				attron(COLOR_PAIR(9));
    			printw("\n\n\n\n\n\n\n\t\t     ()  ()  ()  () \n\t\t     ||  ||  ||  || \n\t\t{~*~*~*~*~*~*~*~*~*~*~} \n\t\t@@@@@@@@@@@@@@@@@@@@@@@ \n\t\t{*~*~*~*~*~*~*~*~*~*~*} \n\t\t@@@@@@@@@@@@@@@@@@@@@@@ \n\t\t{~*~*~*~*~*~*~*~*~*~*~} \n\t\t{*~*~*~*~*~*~*~*~*~*~*} \n\t\t{~*~*~*~*~*~*~*~*~*~*~}\n\t\t@@@@@@@@@@@@@@@@@@@@@@@\n\t\tfrom the gays and doces team, congrats for wining the game \n\t\t\t\tpress any key to quit");
				attroff(COLOR_PAIR(9));
				getch();
				endwin(); exit(0); 
		}
	}
	return 0;
}