#include "defines.h"
#include "ai1.h"
#include "ai2.h"

using namespace std;

//int* game(); //main game procedure

void copy_array(GARRAY ar1, GARRAY ar2); //copy array from first arg to second arg

void clear_board(GARRAY &game_board); //clears board with NONA tokens

void write_field(GARRAY game_board); //for testing purposes, writes board on the screen

bool ckeck_rec(GARRAY game_board, int x, int y, int direction, int count, int token); //recursive function for checking

bool check_win(GARRAY game_board, int token); //checks that if anyone didn't just won
