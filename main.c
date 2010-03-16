#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

#include "defines.h"
#include "ai1.h"
#include "ai2.h"
#include "human.h"

#include "game.h"
#include "graphics.h"


int main(int argc, char *argv[])
{
  if(argc>1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    printf("usage: %s [option] \n\n possible options:\n  -h, --help  show this message \n\ncreated by Garret and Alda (March 2010) \n", argv[0]);
    return 0;
  }

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "SDL: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Surface *screen;
  //SDL_putenv("SDL_VIDEO_CENTERED=1"); //FIXME: okno doprostred, ale vyvola warning pri kompilaci
  screen = SDL_SetVideoMode(MAXY * SIZE_, (MAXX) * SIZE_ + 16, 32, SDL_HWSURFACE);
  if(screen == NULL)
  {
    fprintf(stderr, "SDL: %s\n", SDL_GetError());
    return 1;
  }
  SDL_WM_SetCaption("piskvorky", NULL);

  srand(time(NULL));

  GARRAY game_board;
  coord souradnice;
  int symbol;
  int turns;

  PLAYER player1, player2, playert;
  int player1symbol, player2symbol, playertsymbol;

  player1symbol = CROSS;
  player2symbol = CIRCLE;

  do {
    turns = 0;
    clearBoard(game_board);
    drawBorder(screen);
    if(!drawMenu(screen, &player1, &player2)) {
      return 0;
    }
    if(rand()%2) { // vymena toho, kdo zacina
      playert = player1; playertsymbol = player1symbol;
      player1 = player2; player1symbol = player2symbol;
      player2 = playert; player2symbol = playertsymbol;
    }

    while(1)
    {
      // TODO: zvazit, zda by se SDL_GetKeyState nedalo pouzit pro ukonceni... ja verim, ze ano
      if(turns % 2) {
        symbol = player2symbol;
        souradnice = play(game_board, player2, symbol);
      }
      else {
        symbol = player1symbol;
        souradnice = play(game_board, player1, symbol);
      }

      if(!coordinatesOK(game_board, souradnice)) {
        drawIntoStatusbar(screen, "hra byla ukoncena", WHITE);
        break;
      }

      game_board[souradnice.x][souradnice.y] = symbol;
      drawTurn(screen, souradnice, symbol);
      //SDL_Delay(500);
      ++turns;
      if(checkWin(game_board, souradnice)) {
        drawWin(screen, symbol);
        break;
      }
      if(turns == MAXX*MAXY) {
        drawIntoStatusbar(screen, "remiza", WHITE);
        break;
      }
    }
  } while(game_end(screen));

  SDL_Quit();
  return 0;
}
