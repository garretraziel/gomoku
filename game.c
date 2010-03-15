#include "defines.h"


/*
 * vyprazdneni pole OK
 */
void clearBoard(GARRAY game_board)
{
  for (int i = 0; i < MAXX; i++)
    for (int j = 0; j < MAXY; j++)
      game_board[i][j] = NONA;
}

/*
 * pocita dane znaky na primce s danym smerovym vektorem
 */
int checkFieldWin(GARRAY pole, int x, int y, int dx, int dy, int symbol)
{
  int c = 1;
  for(int i = x + dx, j = y + dy; i >= 0 && j >= 0 && i < MAXX && j < MAXY; i += dx, j += dy) {
    if(pole[i][j] == symbol) {
      ++c;
    }
    else {
      break;
    }  
  }
  for(int i = x - dx, j = y - dy; i >= 0 && j >= 0 && i < MAXX && j < MAXY; i -= dx, j -= dy) {
    if(pole[i][j] == symbol) {
      ++c;
    }
    else {
      break;
    }
  }
  return c >= TOKENS_TO_WIN;
}

/* 
 * kontrola, zda je tah vyherni
 */
int checkWin(GARRAY game_board, coord s)
{
  return checkFieldWin(game_board, s.x, s.y, 1, 0, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, 0, 1, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, 1, 1, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, -1, 1, game_board[s.x][s.y]);
}


/* 
 * vola herni funkci a vraci souradnice
 */
coord play(GARRAY game_board, PLAYER player, int symbol)
{
  coord c;
  c = player(game_board, symbol);
  return c;
}


/*
 * vraci 1, pokud nejsou dane souradnice mimo herni pole a pole je volne, jinak 0
 */
int coordinatesOK(GARRAY game_board, coord s) {
  if(s.x < 0 || s.y < 0 || s.x >= MAXX || s.y >= MAXY || game_board[s.x][s.y] != NONA) {
    return 0;
  }
  else {
    return 1;
  }
}
