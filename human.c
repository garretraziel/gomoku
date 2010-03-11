#include <SDL/SDL.h>

#include "defines.h"

coord human(GARRAY game_board, int symbol)
{
  coord s;
  SDL_Event event;

  s.x = s.y = -1;

  // TODO: dopsat moznost preruseni hry?
  while(1)
  {
    while(!SDL_PollEvent(&event)) SDL_Delay(10); //cekani na nejaky event
    if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
      s.y = event.button.x /= SIZE_;
      s.x = event.button.y /= SIZE_;
      if(game_board[s.x][s.y] == NONA) {
        return s;
      }
    }
    SDL_Delay(10);
  }
}
