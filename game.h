#ifndef GAME_H__
#define GAME_H__

/*
 * vyprazdneni pole
 */
void clearBoard(TGarray game_board);

/*
 * kontrola, zda je tah vyherni
 */
int checkWin(TGarray, TCoord);

/*
 * vraci 1, pokud nejsou dane souradnice mimo herni pole a pole je volne, jinak 0
 */
int coordinatesOK(TGarray, TCoord);

#endif
