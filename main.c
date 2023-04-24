#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"
#include "player.h"
#include "map.h"
#include "bau.h"


/**
 *
 * Um pequeno exemplo que mostra o que se pode fazer
 */
void do_movement_action(PLAYER *st, int dx, int dy) {
	st->playerX += dx;
	st->playerY += dy;
}

void update(PLAYER *st, MAP *mapa) {
	int key = getch();

	//mvaddch(st->playerX, st->playerY, ' ');	//transforma a antiga posicao do player em vazio
	switch(key) {
		case KEY_A1:
		case '7': 
			if((mapa->obj[st->playerX-1][st->playerY-1] != '#' && mapa->obj[st->playerX-1][st->playerY] != '#') || (mapa->obj[st->playerX-1][st->playerY-1] != '#' && mapa->obj[st->playerX][st->playerY-1] != '#'))
				do_movement_action(st, -1, -1);
			break;
		
		case KEY_UP:
		case 'w':
		case 'W':
		case '8':
			if(mapa->obj[st->playerX-1][st->playerY] != '#')
				do_movement_action(st, -1, +0); 
			break;
		
		case KEY_A3:
		case '9': 
			if((mapa->obj[st->playerX-1][st->playerY+1] != '#' && mapa->obj[st->playerX-1][st->playerY] != '#') || (mapa->obj[st->playerX-1][st->playerY+1] != '#' && mapa->obj[st->playerX][st->playerY+1] != '#'))
				do_movement_action(st, -1, +1); 
			break;

		case KEY_LEFT:
		case 'a':
		case 'A':
		case '4': 
			if(mapa->obj[st->playerX][st->playerY-1] != '#')
				do_movement_action(st, +0, -1); 
			break;
		
		case KEY_B2:
		case '5': 
			break;
		
		case KEY_RIGHT:
		case 'd':
		case 'D':
		case '6': 
			if(mapa->obj[st->playerX][st->playerY+1] != '#')
				do_movement_action(st, +0, +1); 
			break;
		
		case KEY_C1:
		case '1': 
			if((mapa->obj[st->playerX+1][st->playerY-1] != '#' && mapa->obj[st->playerX+1][st->playerY] != '#') || (mapa->obj[st->playerX+1][st->playerY-1] != '#' && mapa->obj[st->playerX][st->playerY-1] != '#'))
				do_movement_action(st, +1, -1); 
			break;

		case KEY_DOWN:
		case 's':
		case 'S':
		case '2': {
			if(mapa->obj[st->playerX+1][st->playerY] != '#')
				do_movement_action(st, +1, +0); 
			break;
		}
			
		case KEY_C3:
		case '3': {
			if((mapa->obj[st->playerX+1][st->playerY+1] != '#' && mapa->obj[st->playerX+1][st->playerY] != '#') || (mapa->obj[st->playerX+1][st->playerY+1] != '#' &&  mapa->obj[st->playerX][st->playerY+1] != '#'))
				do_movement_action(st, +1, +1); 
			break;
		}

		case 'q': 
			endwin(); exit(0); 
			break;
	}
}

int main() {
	PLAYER st;
	int i = 0,j = 0,k;
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);



	srand48(time(NULL));
	start_color();

	cbreak();
	noecho();	//nao pegar inputs repetidamente
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);	//pega informacoes do teclado

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

	gerar(&st);

	MAP mapa, fakemapa;

	for(i = 0; i<LINES;i++){
		mapa.obj[i][0] = '#';
		mapa.obj[i][COLS-1] = '#';
	}
	for(j = 1; j<COLS;j++){
		mapa.obj[0][j] = '#';
		mapa.obj[LINES-2][j] = '#';
	}
	for(i = 1; i<LINES-2;i++){
		for(j = 1; j<COLS-1;j++){
			if( rand() % 100 > 40){
			mapa.obj[i][j] = '.';
			}else mapa.obj[i][j] = '#';
		}
	}
	fakemapa = mapa;
	int cont,cont2;
	for(k=0;k < 4; k++){
		for(i = 2; i<LINES-3;i++){
			for(j = 2; j<COLS-2;j++){
				cont = 0;
				cont2 = 0;
				if(mapa.obj[i+1][j] == '#') cont++;
				if(mapa.obj[i+1][j-1] == '#') cont++;
				if(mapa.obj[i+1][j+1] == '#') cont++;
				if(mapa.obj[i][j] == '#') cont++;
				if(mapa.obj[i][j-1] == '#') cont++;
				if(mapa.obj[i][j+1] == '#') cont++;
				if(mapa.obj[i-1][j] == '#') cont++;
				if(mapa.obj[i-1][j-1] == '#') cont++;
				if(mapa.obj[i-1][j+1] == '#') cont++;
				
				if(mapa.obj[i+2][j+2] == '#') cont2++;
				if(mapa.obj[i+2][j-2] == '#') cont2++;
				if(mapa.obj[i+2][j+1] == '#') cont2++;
				if(mapa.obj[i+2][j-1] == '#') cont2++;
				if(mapa.obj[i+2][j] == '#') cont2++;
				if(mapa.obj[i-2][j+2] == '#') cont2++;
				if(mapa.obj[i-2][j-2] == '#') cont2++;
				if(mapa.obj[i-2][j+1] == '#') cont2++;
				if(mapa.obj[i-2][j-1] == '#') cont2++;
				if(mapa.obj[i-2][j] == '#') cont2++;
				if(mapa.obj[i-1][j-2] == '#') cont2++;
				if(mapa.obj[i-1][j+2] == '#') cont2++;
				if(mapa.obj[i][j-2] == '#') cont2++;
				if(mapa.obj[i][j+2] == '#') cont2++;
				if(mapa.obj[i+1][j-2] == '#') cont2++;
				if(mapa.obj[i+1][j+2] == '#') cont2++;
				

				if(cont >= 5 || cont2 <= 2){
					fakemapa.obj[i][j] = '#';
				}else{
					fakemapa.obj[i][j] = '.';
				}
			}
		}
		mapa = fakemapa;
	}

	for(k=0;k < 3; k++){
		for(i = 2; i<LINES-3;i++){
			for(j = 2; j<COLS-2;j++){
				cont = 0;
				if(mapa.obj[i+1][j] == '#') cont++;
				if(mapa.obj[i+1][j-1] == '#') cont++;
				if(mapa.obj[i+1][j+1] == '#') cont++;
				if(mapa.obj[i][j] == '#') cont++;
				if(mapa.obj[i][j-1] == '#') cont++;
				if(mapa.obj[i][j+1] == '#') cont++;
				if(mapa.obj[i-1][j] == '#') cont++;
				if(mapa.obj[i-1][j-1] == '#') cont++;
				if(mapa.obj[i-1][j+1] == '#') cont++;

				if(cont >= 5){
					
				}else{
					fakemapa.obj[i][j] = '.';
				}

			}
		}
		mapa = fakemapa;
	}	



	/**
	 * Este código está muito mal escrito!
	 * Deveria existir uma função chamada draw_player!
	 *
	 * Se estamos a desenhar uma luz à volta do jogador
	 * deveria existir uma função chamada draw_light!
	 *
	 */
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		int nivel = st.nivel;
		if (nivel>=5){
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d Agua Benta:%d", st.playerX, st.playerY, ncols, nrows, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
		} else{
			printw("(%d, %d) %d %d Nivel:%d Vida:%d/%d Defesa:%d Flechas:%d Espada:%d Arco:%d Pocoes de Vida:%d ???:%d", st.playerX, st.playerY, ncols, nrows, st.nivel, st.vida, st.vidamaxima, st.defesa, st.flechas, st.ataqueespada, st.ataquearco, st.pocoesvida, st.aguabenta);
		}
		attroff(COLOR_PAIR(COLOR_BLUE));

		attron(COLOR_PAIR(COLOR_YELLOW));
		for(i = 0; i<LINES-1;i++){
			for(j = 0; j<COLS;j++){
				if((i == st.playerX) && (j == st.playerY)){
					mvaddch(i, j, '@' | A_BOLD);
				}else mvaddch(i, j, mapa.obj[i][j] | A_BOLD);
			}
		}
		attroff(COLOR_PAIR(COLOR_YELLOW));
/*		attron(COLOR_PAIR(COLOR_WHITE));
		mvaddch(st.playerX, st.playerY, '@' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_WHITE));
		attron(COLOR_PAIR(COLOR_YELLOW));
		mvaddch(st.playerX - 1, st.playerY - 1, '.' | A_BOLD);
		mvaddch(st.playerX - 1, st.playerY + 0, '.' | A_BOLD);
		mvaddch(st.playerX - 1, st.playerY + 1, '.' | A_BOLD);
		mvaddch(st.playerX + 0, st.playerY - 1, '.' | A_BOLD);
		mvaddch(st.playerX + 0, st.playerY + 1, '.' | A_BOLD);
		mvaddch(st.playerX + 1, st.playerY - 1, '.' | A_BOLD);
		mvaddch(st.playerX + 1, st.playerY + 0, '.' | A_BOLD);
		mvaddch(st.playerX + 1, st.playerY + 1, '.' | A_BOLD);
        attroff(COLOR_PAIR(COLOR_YELLOW));	*/
		move(st.playerX, st.playerY);
		update(&st, &mapa);
	}

	return 0;
}
