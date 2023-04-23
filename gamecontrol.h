#ifndef ___GAMECONTROL_H___
#define ___GAMECONTROL_H___

#include "inimigo.h"

typedef struct control{
INIMIGO inimigodem[100];
INIMIGO inimigodfnt[100];
INIMIGO inimigovmp[100];
int nivel;
int bauspawn;
int qntdem;
int qntfnt;
int qntvmp;
} CONTROL;

#endif
    // inimigos, nivel atual de mapa, bau