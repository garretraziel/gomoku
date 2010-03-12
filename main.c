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


//int WinMain(int argc, char *argv[])
int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "SDL: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Surface *screen;
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

  // TODO: udelat menu pro vyber, kdo hraje H+AI, AI+AI
  player1 = human;
  player1symbol = CROSS;
  player2 = ai2;
  //player2 = ai1;
  player2symbol = CIRCLE;
  //playerx = humann;

  do {
    // reset hry
    turns = 0;
    clearBoard(game_board);
    SDL_FillRect(screen, NULL, 0);
    drawBorder(screen);
    if(rand()%2) { // vymena toho, kdo zacina
      playert = player1; playertsymbol = player1symbol;
      player1 = player2; player1symbol = player2symbol;
      player2 = playert; player2symbol = playertsymbol;
    }
    while(1)
    {
      // TODO: je potreba kontrolovat, zda AI neopravnene nepise do pole?
      if(turns % 2) {
        symbol = player2symbol;
        souradnice = play(game_board, player2, symbol);
      }
      else {
        symbol = player1symbol;
        souradnice = play(game_board, player1, symbol);
      }
      drawTurn(screen, souradnice, symbol);
      game_board[souradnice.x][souradnice.y] = symbol;
      if(checkWin(game_board, souradnice)) {
        drawWin(screen, symbol);
        break;
      }
      ++turns;
      if(turns == MAXX*MAXY) {
        drawDraw(screen);
        break;
      }
    }
  } while(game_end(screen));

  SDL_Quit();
  return 0;
}
