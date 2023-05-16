#include "map.h"
#include "posicao.h"
#include "movimento.h"
#include "bau.h"
#include "player.h"
#include "gamecontrol.h"

void gerarmapa(int bauspawn,MAP *mapa,PLAYER *st, POSICAO max);

void gerarplayer(MAP *mapa,PLAYER *st,POSICAO max);

void gerarsaida(MAP *mapsaida, POSICAO max);

int ativarsaida(CONTROL *gamecontroller,PLAYER *s,MAP *mapsaida, POSICAO max);

void gerar(PLAYER *s);