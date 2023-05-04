#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "movimento.h"

POSICAO do_movement_action(POSICAO st, int dx, int dy) {
	st.posX += dx;
	st.posY += dy;
	return st;
}
