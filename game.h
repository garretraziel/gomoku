/*
 * (c) Garret Raziel and Alda (2010)
 * released under GNU/GPL v.3,
 * for further details, see LICENCE
 */

#ifndef GAME_H__
#define GAME_H__

/*
 * naplni herni pole symbolem pro volno
 */
void clearBoard(TGarray game_board);

/*
 * kontrola, zda je tah vyherni
 * pokud je vyherni, vraci 1, jinak 0
 */
int checkWin(TGarray, TCoord);

/*
 * overuje spravnost souradnic
 * pokud nejsou dane souradnice mimo pole a policko je volne, vraci 1, jinak 0
 */
int coordinatesOK(TGarray, TCoord);

/*
 * smycka na konci hry
 * zjisti, zda chce hrac hrat znovu, ukoncit program, nebo se vratit do menu
 */
int endGame(void);

#endif
