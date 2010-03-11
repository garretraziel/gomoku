#include <stdlib.h>
#include "defines.h"

coord ai1(GARRAY game_board, int symbol)
{
  coord c;
  c.x = rand()%MAXX;
  c.y = rand()%MAXY;
  return c;
}
