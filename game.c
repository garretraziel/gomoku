#include "defines.h"


// vyprazdneni pole OK
void clearBoard(GARRAY game_board)
{
  for (int i = 0; i < MAXX; i++)
    for (int j = 0; j < MAXY; j++)
      game_board[i][j] = NONA;
}

// pocita dane znaky na primce s danym smerovym vektorem
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

// kontrola, zda je tah vyherni
int checkWin(GARRAY game_board, coord s)
{
  return checkFieldWin(game_board, s.x, s.y, 1, 0, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, 0, 1, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, 1, 1, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, -1, 1, game_board[s.x][s.y]);
}


// vola herni funkci a vraci souradnice, pokud jsou v poradku
coord play(GARRAY game_board, PLAYER player, int symbol)
{
  coord c;

  // TODO: pokud se nekdo snazi hrat kam nema, co se bude dit? ted je loop, ja bych ho dal pryc aukoncil hru
//  while(1)
//  {
    c = player(game_board, symbol);
    if(c.x >= 0 && c.x < MAXX && c.y >= 0 && c.y < MAXY && game_board[c.x][c.y] == NONA ) {
      return c;
    }
//  }
  return c;
}
