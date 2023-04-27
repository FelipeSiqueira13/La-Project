#ifndef ___PLAYER_H___
#define ___PLAYER_H___

#include  "posicao.h"

typedef struct player{
	POSICAO pos;
	int nivel;
	int vida;
	int vidamaxima;
	int defesa;
	int flechas;
	int ataqueespada;
	int ataquearco;
	int pocoesvida;
	int aguabenta;
} PLAYER;

#endif