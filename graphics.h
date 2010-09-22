#ifndef GRAPHICS_H__
#define GRAPHICS_H__

#include "defines.h"

/* 
 * vykresluje mrizku hraciho pole
 */
int drawBorder(SDL_Surface*);

/*
 * vykresluje znacky do hraciho pole
 */
int drawTurn(SDL_Surface*, TCoord, int);

/*
 * vymazani statusbaru
 */
int clearStatusbar(SDL_Surface*);

/*
 * vypis textu do statusbaru
 */
int drawIntoStatusbar(SDL_Surface*,char*,int);

/*
 * vypise do statusbaru, kdo vyhral
 */
int drawWin(SDL_Surface*, int);

/*
 * vypis menu a nastaveni, kdo hraje
 */
int drawMenu(SDL_Surface*, TPlayer*, TPlayer*);

#endif
