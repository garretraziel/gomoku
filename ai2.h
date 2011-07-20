/*
 * (c) Garret Raziel and Alda (2010)
 * released under GNU/GPL v.3,
 * for further details, see LICENCE
 */

#ifndef AI2_H__
#define AI2_H__

/*
 * hlavni funkce AI - vyhleda v poli nejlepsi tah a vrati souradnice
 * souradnice policek s nejvyssi prioritou uklada do zasobniku, odkud
 * je nahodne jeden tah vylosovan
 */
TCoord ai2(TGarray, int);

#endif
