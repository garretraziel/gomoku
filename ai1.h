#ifndef AI1_H
#define AI1_H
#include "defines.h"
// FEEL free to do anything with your class to be the best AI in the five-in-a-row!
// but remember, do not change standard metod play to anything other and
// never, I said NEVER touch the main.cpp and defines.h file

class ai1
{
    public:
        ai1() {turns=1;}
        virtual ~ai1();
        DIRECTIONS play(GARRAY &game_board);
    protected:
		int turns;
		bool testmode(GARRAY game_board, int token, int pos);
		bool check_rec(GARRAY game_board, int x, int y, int direction, int &count, int token, int count_to_win);
		bool check_win(GARRAY game_board, int token, int count_to_win=TOKENS_TO_WIN);
		bool check_act(GARRAY game_board, int token, int i, int j, int towin=TOKENS_TO_WIN);
};

#endif // AI1_H
