#include "player.h"
#include "gamecontrol.h"


#ifndef ___CARDS_H___
#define ___CARDS_H___

#include  "posicao.h"

typedef struct card{
    int id;
    char texto[300];
} CARD;

typedef struct cards
{
    CARD commum[10];
    CARD rare[8];
}CARDS;


#endif
void startcards(CARDS *cards);

void callACard(PLAYER *st, CONTROL *gamecontrol,CARDS cards);

void activecard(int id,PLAYER *st, CONTROL *gamecontrol);