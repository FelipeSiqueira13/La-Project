#ifndef ___PLAYER_H___
#define ___PLAYER_H___

#include  "posicao.h"

typedef struct player{
	POSICAO pos;
	int debugmode;
	int nivel;
	int vida;
	int vidamaxima;
	int defesa;
	int flechas;
	int ataqueespada;
	int danoespada;
	int ataquearco;
	int danoarco;
	int pocoesvida;
	int aguabenta;
	int ataquepronto;
	int pocaopronta;
}PLAYER;

#endif