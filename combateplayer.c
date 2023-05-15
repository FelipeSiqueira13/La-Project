#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "combateplayer.h"

void ataqueplayer(INIMIGO *s, PLAYER *r){
    if (s->vidainimigo > 0 && ((rand()%21) + r->ataqueespada) >= s->defesainimigo){
        s->vidainimigo -= ((2*(rand() % 4) + 1) + r->danoespada); 
    }
}