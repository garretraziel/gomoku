#ifndef AI2_H
#define AI2_H
#include "defines.h"
// FEEL free to do anything with your class to be the best AI in the five-in-a-row!
// but remember, do not change standard metod play to anything other and
// never, I said NEVER touch the main.cpp and defines.h file

class ai2
{
    public:
        ai2();
        virtual ~ai2();
        DIRECTIONS play(GARRAY &game_board);
    protected:
    private:
};

#endif // AI2_H
