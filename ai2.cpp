#include "ai2.h"

ai2::ai2()
{
    //ctor
}

ai2::~ai2()
{
    //dtor
}

DIRECTIONS ai2::play(GARRAY &game_board)
{
    DIRECTIONS dir;
    dir.x=1;
    dir.y=2;
    //HERE past what must to be hapen when it's your turn
    // function uses GARRAY, which is array 0-MAXX and 0-MAXY (both 15 by default) of integer
    // const CIRCLE from defines.h represent circle (and it is number 2 by default), CROSS (1 by def)
    // represent cross token and NONA (0 by def) represent empty field
    //
    // function returns true if all have been done well and false if there was some errors
    //
    // IT IS FORBIDDEN TO CHANGE ALREADY PLACED TOKENS!
    return dir;
}
