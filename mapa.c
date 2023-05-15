#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"

void gerar(PLAYER *s,MAP *mapa, POSICAO max) {
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