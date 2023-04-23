#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mudarmapa.h"
#include "calcdist.h"
#include "gerarmapa.h"

void ativarsaida(int bauspawn,PLAYER *s,MAP *mapsaida, POSICAO max){
    int X;
    int Y;
    X = s->pos.posX;
    Y = s->pos.posY;
    if ('S' == mapsaida->obj[X][Y]){
        gerarmapa(bauspawn,mapsaida, max);
    }
}
// se estiver em cima de uma saída usar a função em gerarmapa.h para gerar um novo mapa