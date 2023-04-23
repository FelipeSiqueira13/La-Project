#ifndef ___INIMIGO_H___
#define ___INIMIGO_H___

#include  "posicao.h"

typedef struct inimigo{
    POSICAO pos;
    int vidainimigo;
    int defesainimigo;
    int ataqueinimigo;
    int danoinimigo;
    int trigger; //trigger vai ser ou 1 ou 0, sendo 1=ele ve o jogador e 0=ele nao ve
} INIMIGO;

#endif