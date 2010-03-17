#include <SDL/SDL.h>

#include "defines.h"


/*
 * vyprazdneni pole OK
 */
void clearBoard(TGarray game_board)
{
  for (int i = 0; i < MAXX; i++)
    for (int j = 0; j < MAXY; j++)
      game_board[i][j] = NONA;
}


/*
 * pocita dane znaky na primce s danym smerovym vektorem
 */
int checkFieldWin(TGarray pole, int x, int y, int dx, int dy, int symbol)
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
int checkWin(TGarray game_board, TCoord s)
{
  return checkFieldWin(game_board, s.x, s.y, 1, 0, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, 0, 1, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, 1, 1, game_board[s.x][s.y]) ||
   checkFieldWin(game_board, s.x, s.y, -1, 1, game_board[s.x][s.y]);
}


/*
 * vraci 1, pokud nejsou dane souradnice mimo herni pole a pole je volne, jinak 0
 */
int coordinatesOK(TGarray game_board, TCoord s) {
  if(s.x < 0 || s.y < 0 || s.x >= MAXX || s.y >= MAXY || game_board[s.x][s.y] != NONA) {
    return 0;
  }
  else {
    return 1;
  }
}


/*
 * smycka na konci hry
 */
int endGame(void)
{
  SDL_Event event;
  Uint8 *keys;

  while(1) {
    if(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        return EXIT;
      }   
      keys = SDL_GetKeyState(NULL);
      if(keys[SDLK_q] || keys[SDLK_ESCAPE] || keys[SDLK_RETURN]) {
        return EXIT;
      }   
      else if(keys[SDLK_r]) {
        return RESTART;
      }   
      else if(keys[SDLK_m]) {
        return MENU;
      }   
    }   
    SDL_Delay(10); // kvuli CPU zatezi
  }
}
