#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "bau.h"

void novositens(PLAYER *s){
    int nivel = s->nivel;
    if (nivel>=5){
        s->aguabenta += rand() % 3;
        s->flechas += rand() % 41;
        s->pocoesvida += rand() % 5;
    } else {
        s->flechas += rand() % 21;
        s->pocoesvida += rand() % 3;
    }
}