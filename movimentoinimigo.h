#include "posicao.h"
#include "map.h"
#include "vision.h"
#include "gerarinimigodem.h"
#include "gerarinimigofant.h"
#include "calcdist.h"
#include "obstaculo.h"
#include "movimento.h"

void movimento_do_inimigo_dem(PLAYER *st, INIMIGO *s, MAP *r);

void movimento_do_inimigo_fant(PLAYER *st, INIMIGO *s, MAP *r);
