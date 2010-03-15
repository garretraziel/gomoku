#include <SDL/SDL.h>

#include "defines.h"


/*
 * funkce pro precteni, kam chce hrat clovek
 * vraci souradnice vybraneho tahu nebo [-1,-1] pokud me byt hra ukoncena
 *    game_board - hraci pole
 *    symbol - znacka hrace
 */
coord human(GARRAY game_board, int symbol)
{
  coord s;
  SDL_Event event;

  while(1)
  {
    if(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)) {
        s.x = s.y = -1;
        return s;
      }
      if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        s.y = event.button.x /= SIZE_;
        s.x = event.button.y /= SIZE_;
        if(game_board[s.x][s.y] == NONA) {
          return s;
        }
      }
    }
    SDL_Delay(10);
  }
}
