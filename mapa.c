#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"

void gerar(PLAYER *s) {
	s->playerX = 10;
	s->playerY = 10;
}
