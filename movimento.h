#include "posicao.h"
#include "map.h"

POSICAO do_movement_action(POSICAO st, int dx, int dy, MAP *mapa);

int obstaculo(POSICAO pos, MAP *mapa, int dx, int dy);