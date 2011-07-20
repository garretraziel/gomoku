#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "defines.h"
#include "ai1.h"
#include "ai2.h"
#include "human.h"


/*
 * vykresluje znacky do hraciho pole
 */
int drawTurn(SDL_Surface *screen, TCoord c, int player)
{
  if(player == CROSS) {
    lineColor(screen, c.y * FIELD_SIZE + 2, c.x * FIELD_SIZE + 2, c.y * FIELD_SIZE + FIELD_SIZE - 2, c.x * FIELD_SIZE + FIELD_SIZE - 2, 0xff0000ff);
    lineColor(screen, c.y * FIELD_SIZE + FIELD_SIZE - 2, c.x * FIELD_SIZE + 2, c.y * FIELD_SIZE + 2, c.x * FIELD_SIZE + FIELD_SIZE - 2, 0xff0000ff);
  }
  else {
    circleColor(screen, c.y * FIELD_SIZE + FIELD_SIZE / 2, c.x * FIELD_SIZE + FIELD_SIZE / 2, FIELD_SIZE / 2 - 2, 0xffff00ff);
  }
  SDL_UpdateRect(screen, 0,0,0,0);
  return 0;
}

/* 
 * vykresluje mrizku hraciho pole
 */
int drawBorder(SDL_Surface *screen)
{
  SDL_FillRect(screen, NULL, BLACK);
  for(int i = 1; i < MAXX+1; ++i) {
    hlineColor(screen, 0, MAXY * FIELD_SIZE, i * FIELD_SIZE, 0xffffff50);
  }
  for(int i = 1; i < MAXY; ++i) {
    vlineColor(screen, i * FIELD_SIZE, 0, MAXX * FIELD_SIZE, 0xffffff50);
  }
  SDL_UpdateRect(screen, 0,0,0,0);
  return 0;
}

/*
 * vymazani statusbaru
 */
int clearStatusbar(SDL_Surface *screen)
{
  SDL_Rect statusbar = {.x = 0, .y = MAXX * FIELD_SIZE+1, .w = MAXY * FIELD_SIZE, .h = STATUSBAR_SIZE};
  SDL_FillRect(screen, &statusbar, BLACK);
  SDL_UpdateRect(screen, 0,0,0,0);
  return 0;
}

/*
 * vypis textu do statusbaru
 */
int drawIntoStatusbar(SDL_Surface *screen, char* message, int color)
{
  clearStatusbar(screen);
  stringColor(screen, 5, FIELD_SIZE * MAXX + 5, message, color);
  SDL_UpdateRect(screen, 0,0,0,0);
  return 0;
}

/*
 * vypise do statusbaru, kdo vyhral
 */
int drawWin(SDL_Surface *screen, int player)
{
  if(player == CROSS) {
    drawIntoStatusbar(screen,"crosses won [q]uit [r]estart [m]enu", RED);
  }
  else {
    drawIntoStatusbar(screen,"circles won [q]uit [r]estart [m]enu", YELLOW);
  }
  return 0;
}

/*
 * vypis menu a nastaveni, kdo hraje
 */
int drawMenu(SDL_Surface *screen, TPlayer* player1, TPlayer* player2)
{
  drawIntoStatusbar(screen, "[F1] AIxAI, [F2] AI1, [F3] AI2, [F4] human x human", WHITE);
  SDL_Event event;

  while(1) {
    if(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        return 0;
      }
      if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_F1:
            *player1 = ai1;
            *player2 = ai2;
            clearStatusbar(screen);
            //drawIntoStatusbar(screen,"hraji @G(X) a @A(O)", WHITE);
            return 1;
          case SDLK_F2:
            *player1 = ai1;
            *player2 = human;
            clearStatusbar(screen);
            //drawIntoStatusbar(screen,"hrajete proti @G(X)", WHITE);
            return 1;
          case SDLK_F3:
            *player1 = human;
            *player2 = ai2;
            clearStatusbar(screen);
            //drawIntoStatusbar(screen,"hrajete proti @A(O)", WHITE);
            return 1;
          case SDLK_F4:
            *player1 = human;
            *player2 = human;
            clearStatusbar(screen);
            //drawIntoStatusbar(screen,"hraji hraci", WHITE);
            return 1;
          case SDLK_q:
          case SDLK_ESCAPE:
          case SDLK_RETURN:
            return 0;
          default:
            break;
        }
      }
    }
    SDL_Delay(10);
  }
}
