#include "defines.h"
#include "ai1.h"
#include "ai2.h"
#include "human.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/*
 * vykresluje znacky do hraciho pole
 */
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

/* 
 * vykresluje mrizku hraciho pole
 */
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

/*
 * vypis textu do statusbaru
 */
int drawIntoStatusbar(SDL_Surface *screen, char* message, int color)
{
  stringColor(screen, 5, SIZE_ * MAXX + 5, message, color);
  return 0;
}

/*
 * vypise do statusbaru, kdo vyhral
 */
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

/*
 * vypis menu a nastaveni, kdo hraje
 */
int drawMenu(SDL_Surface *screen, PLAYER* player1, PLAYER* player2)
{
  drawIntoStatusbar(screen, "[F1] AIxAI, [F2] AI1, [F3] AI2, [F4] human x human", WHITE);
  SDL_Event event;
  Uint8 *keys;

  SDL_UpdateRect(screen, 0,0,0,0);
  while(1) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        return 0;
      }
    }
    // TODO: tohle prepsat nejak usporneji, takhle to vypada priserne
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

/*
 * smyska na konci hry
 */
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
