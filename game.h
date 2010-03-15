#ifndef GAME_H__
#define GAME_H__

/*
 * vyprazdneni pole OK
 */
void clearBoard(GARRAY game_board);

/*
 * kontrola, zda je tah vyherni
 */
int checkWin(GARRAY, coord);

/*
 * vola herni funkci a vraci souradnice
 */
coord play(GARRAY, PLAYER, int);

/*
 * vraci 1, pokud nejsou dane souradnice mimo herni pole a pole je volne, jinak 0
 */
int coordinatesOK(GARRAY, coord);

#endif
