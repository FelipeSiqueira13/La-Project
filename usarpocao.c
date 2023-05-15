#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "usarpocao.h"

void usarpocao(PLAYER *r){
    if (r->pocoesvida > 0){
        r->vida += (20 + (r->vidamaxima * 0.1));
        if (r->vida > r->vidamaxima){
            r->vida = r->vidamaxima;
        }
        r->pocoesvida -= 1;
    }
}