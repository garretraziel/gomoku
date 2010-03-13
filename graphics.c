#include "defines.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>


// udelani tahu umele inteligence OK
int drawTurn(SDL_Surface *screen, coord c, int player)
{
  if(player == CROSS) {
    lineColor(screen, c.y * SIZE_ + 2, c.x * SIZE_ + 2, c.y * SIZE_ + SIZE_ - 2, c.x * SIZE_ + SIZE_ - 2, 0xff0000ff);
    lineColor(screen, c.y * SIZE_ + SIZE_ - 2, c.x * SIZE_ + 2, c.y * SIZE_ + 2, c.x * SIZE_ + SIZE_ - 2, 0xff0000ff);
  }
  else {
    circleColor(screen, c.y * SIZE_ + SIZE_ / 2, c.x * SIZE_ + SIZE_ / 2, SIZE_ / 2 - 2, 0xffff00ff);
  }
  SDL_UpdateRect(screen, 0,0,0,0);
  return 0;
}


// udela ramecek
int drawBorder(SDL_Surface *screen)
{
  for(int i = 1; i < MAXY + 1; ++i) {
    hlineColor(screen, 0, MAXY * SIZE_, i * SIZE_, 0xffffff50);
  }
  for(int i = 1; i < MAXX; ++i) {
    vlineColor(screen, i * SIZE_, 0, MAXX * SIZE_, 0xffffff50);
  }
  SDL_UpdateRect(screen, 0,0,0,0);
  return 0;
}


// vypisuje oznameni o vyhre hrace
int drawWin(SDL_Surface *screen, int player)
{
  if(player == CROSS) {
    stringColor(screen, 5, SIZE_ * MAXX + 5, "vyhraly krizky", 0xff0000ff);
  }
  else {
    stringColor(screen, 5, SIZE_ * MAXX + 5, "vyhrala kolecka", 0xffff00ff);
  }
  return 0;
}


// vypisuje oznameji o remize
int drawDraw(SDL_Surface *screen)
{
  stringColor(screen, 5, SIZE_ * MAXX + 5, "remiza", 0xffffffff);
  return 0;
}


// loop na konci hry, reset ? konec
int game_end(SDL_Surface *screen)
{
  SDL_Event event;
  Uint8 *keys;

  SDL_UpdateRect(screen, 0,0,0,0);
  while(1) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        return 0;
      }
    }
    keys = SDL_GetKeyState(NULL);
    if(keys[SDLK_q] || keys[SDLK_ESCAPE] || keys[SDLK_RETURN]) {
      return 0;
    }
    if(keys[SDLK_r]) {
      return 1;
    }
    SDL_Delay(10); // kvuli CPU zatezi
  }
}


/* TODO: dodelat, predelat, vylepsit
int selectPlayers(SDL_Surface *screen)
{
  rectangleColor(screen, 2 * SIZE_, 2 * SIZE_, (MAXX - 2) * SIZE_, 3 * SIZE_, 0x00ff00ff); 
  rectangleColor(screen, 2 * SIZE_, 4 * SIZE_, (MAXX - 2) * SIZE_, 5 * SIZE_, 0xffff00ff); 
  rectangleColor(screen, 2 * SIZE_, 6 * SIZE_, (MAXX - 2) * SIZE_, 7 * SIZE_, 0xff0000ff);

  stringColor(screen, MAXX * SIZE_ / 2 - 7 * 8 / 2, 2 * SIZE_ + 5, "PC x PC",  0x00ff00ff);
  stringColor(screen, MAXX * SIZE_ / 2 - 7 * 8 / 2, 4 * SIZE_ + 5, " jeden ", 0xffff00ff);
  stringColor(screen, MAXX * SIZE_ / 2 - 7 * 8 / 2, 6 * SIZE_ + 5, " druhy ",  0xff0000ff);

  SDL_UpdateRect(screen, 0,0,0,0);
    
  SDL_Event eventa;
  int x, y;

  while(1)
  {
    SDL_PollEvent(&eventa);
    if(eventa.type == SDL_MOUSEBUTTONDOWN && eventa.button.button == SDL_BUTTON_LEFT)
    {
      x = eventa.button.x;
      y = eventa.button.y;
      if(x <= (MAXX - 2) * SIZE_ && x >= 2 * SIZE_ && y <= 3 * SIZE_ && y >= 2 * SIZE_)
        return 1;
      else if(x <= (MAXX - 2) * SIZE_ && x >= 2 * SIZE_ && y <= 5 * SIZE_ && y >= 4 * SIZE_)
        return 2;
      else if(x <= (MAXX - 2) * SIZE_ && x >= 2 * SIZE_ && y <= 7 * SIZE_ && y >= 6 * SIZE_)
        return 3;
    }
    else if(eventa.type == SDL_KEYDOWN && eventa.key.keysym.sym == SDLK_q)
      return 0;
    SDL_Delay(10);
  }
}
*/
