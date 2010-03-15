#include "defines.h"
#include "ai1.h"
#include "ai2.h"
#include "human.h"

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

int drawIntoStatusbar(SDL_Surface *screen, char* message, int color)
{
  stringColor(screen, 5, SIZE_ * MAXX + 5, message, color);
  return 0;
}

// vypisuje oznameni o vyhre hrace
int drawWin(SDL_Surface *screen, int player)
{
  if(player == CROSS) {
    drawIntoStatusbar(screen,"vyhraly krizky", RED);
  }
  else {
    drawIntoStatusbar(screen,"vyhraly kolecka", YELLOW);
  }
  return 0;
}


// vypisuje oznameji o remize
int drawDraw(SDL_Surface *screen)
{
  drawIntoStatusbar(screen, "remiza", WHITE);
  return 0;
}

int drawMenu(SDL_Surface *screen, PLAYER* player1, PLAYER* player2)
{
  drawIntoStatusbar(screen, "[F1] AIxAI, [F2] AI1, [F3] AI2, [F4] human x human", WHITE);
  SDL_Event event;
  Uint8 *keys;

  SDL_UpdateRect(screen, 0,0,0,0);
  while(1) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        return 1;
      }
    }
    keys = SDL_GetKeyState(NULL);
    if(keys[SDLK_F1]) {
      *player1 = ai1;
      *player2 = ai2;
      return 0;
    }
    if(keys[SDLK_F2]) {
      *player1 = ai1;
      *player2 = human;
      return 0;
    }
    if(keys[SDLK_F3]) {
      *player1 = ai2;
      *player2 = human;
      return 0;
    }
    if(keys[SDLK_F4]) {
      *player1 = human;
      *player2 = human;
      return 0;
    }
    if(keys[SDLK_q] || keys[SDLK_ESCAPE] || keys[SDLK_RETURN]) {
      return 1;
    }
    SDL_Delay(10);
  }
  return 1;
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
player_list selectPlayers(SDL_Surface *screen)
{
  player_list players;
  players.player1 = 1;
  players.player2 = 3;
  rectangleColor(screen, 2 * SIZE_, 2 * SIZE_, (MAXX - 2) * SIZE_, 3 * SIZE_, 0x00ff00ff); 
  //rectangleColor(screen, 2 * SIZE_, 4 * SIZE_, (MAXX - 2) * SIZE_, 5 * SIZE_, 0xffff00ff); 
  //rectangleColor(screen, 2 * SIZE_, 6 * SIZE_, (MAXX - 2) * SIZE_, 7 * SIZE_, 0xff0000ff);

  stringColor(screen, MAXX * SIZE_ / 2 - 7 * 8 / 2, 2 * SIZE_ + 5, "New Game",  0x00ff00ff);
  //stringColor(screen, MAXX * SIZE_ / 2 - 7 * 8 / 2, 4 * SIZE_ + 5, " jeden ", 0xffff00ff);
  //stringColor(screen, MAXX * SIZE_ / 2 - 7 * 8 / 2, 6 * SIZE_ + 5, " druhy ",  0xff0000ff);

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
        return players;
    }
    else if(eventa.type == SDL_KEYDOWN && eventa.key.keysym.sym == SDLK_q)
    {
      players.player1 = 0;
      return players;
    }
    SDL_Delay(10);
  }
}*/
