#include "inimigo.h"
#include "player.h"
#include "map.h"

void ataqueini(INIMIGO *s, PLAYER *r, MAP mapa, int distrange);

void ataqueplayer(INIMIGO *s, PLAYER *r, MAP *mapa);

void ataqueplayerdistancia(INIMIGO *s, PLAYER *r, MAP *mapa);