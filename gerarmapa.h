#include "map.h"
#include "posicao.h"
#include "movimento.h"
#include "bau.h"
#include "player.h"
#include "gamecontrol.h"

void gerarmapa(int bauspawn, MAP *mapa, PLAYER *st, POSICAO max);
//Felipe Espinheira

void gerarplayer(MAP *mapa, PLAYER *st, POSICAO max);
//Felipe Espinheira

void gerarsaida(MAP *mapsaida, POSICAO max);
//Felipe Espinheira

int ativarsaida(CONTROL *gamecontroller, PLAYER *s, MAP *mapsaida, POSICAO max);
//Felipe Espinheira

void gerar(PLAYER *s);
//Felipe Espinheira
