#include "defines.h"

int drawBorder(SDL_Surface*);
int drawTurn(SDL_Surface*, coord, int);
int drawIntoStatusbar(SDL_Surface*,char*,int);
int drawWin(SDL_Surface*, int);
int drawDraw(SDL_Surface*);
int drawMenu(SDL_Surface*, PLAYER*, PLAYER*);

//player_list selectPlayers(SDL_Surface*);

int game_end(SDL_Surface*);
