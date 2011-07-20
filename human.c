/*
 * (c) Garret Raziel and Alda (2010)
 * released under GNU/GPL v.3,
 * for further details, see LICENCE
 */

#include <SDL/SDL.h>

#include "defines.h"

/*
 * funkce vraci souradnice, kam chce hrac hrat
 * v pripade, ze chce hrac hru ukoncit, vraci souradnice mimo hraci pole
 *    game_board - hraci pole
 *    symbol - znacka hrace
 */
TCoord human(TGarray game_board, int symbol)
{
  TCoord s;
  SDL_Event event;

  while(1)
  {
    if(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)) { // TODO: konec i na dalsi klavesy, mozna prepsat do switch
        s.x = s.y = -1;
        return s;
      }
      if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        s.y = event.button.x /= FIELD_SIZE;
        s.x = event.button.y /= FIELD_SIZE;
        if(game_board[s.x][s.y] == NONA) {
          return s;
        }
      }
    }
    SDL_Delay(10);
  }
}
