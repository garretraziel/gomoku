#include <stdio.h>
#include <stdlib.h>

#include "defines.h"


/*
 * structura obsahujici informace o moznem tahu
 *   symbols - pocet znacek v rade
 *   size - celkova velikost rady znacek a volnych mist
 *   space - zda rada znacek je prerusena
 *   free - zda jsou na konci rady volna policka
 */
typedef struct {
  int symbols;
  int size;
  int space;
  int free;
} TFieldValue;


/*
 * structura popisujici prvek v zasobniku
 *   val - uchovava souradni tahu
 *   next - ukazatel na pristi prvek zasobniku
 */
typedef struct node {
  TCoord val;
  struct node *next;
} TNode;

/*
 * vlozeni prvku do zasobniku
 * pokud se z nejakeho duvodu nepodari allocovat dalsi prvek, vraci false, jinak true
 *   root - ukazatel na ukazatel na vrchol zasobniku
 *   val - hodnota k ulozeni do zasobniku
 * TODO: zamyslet se, kam se vkladaji prvky do zasobniku
 */
int stackInsert(TNode **root, TCoord val)
{
  if(*root == NULL) {
    *root = malloc(sizeof(TNode));
    if(*root == NULL) {
      return 0;
    }
    (*root)->val = val;
    (*root)->next = NULL;
    return 1;
  }
  else {
    return stackInsert(&(*root)->next, val);
  }
}

/*
 * smazani celeho zasobniku
 * uvolni vsechnu pamet pouzivanou zasobnikem a ukazatel na vrchol nastavi na NULL
 *   root - ukazatel na ukazatel na vrchol zasobnika
 */
int stackDrop(TNode **root)
{
  if(*root == NULL) {
    return 1;
  }
  TNode *t = (*root)->next;
  free(*root);
  *root = NULL;
  return stackDrop(&t);
}

/*
 * vrati v poradi n-ty prvek ze zasobniku
 *   root - ukazatel na vrchol zasobnika
 *   n - kolikty prvek vratit
 */
TCoord stackGet(TNode *root, int n)
{
  if(n > 0) {
    return stackGet(root->next, n-1);
  }
  return root->val;
}



/*
 * vypocita pocet danych znaku v rade, pocet mezer, ktere se tam vyskutuji a delku volneho mista
 *    pole - herni pole
 *    x - x souradnice pole
 *    y - y souradnice pole
 *    dx - smer vypoctu po x
 *    dy - smer vypoctu po y
 *    symbol - znak hrace
 */
TFieldValue vsechnysmery(TGarray pole, int x, int y, int dx, int dy, int symbol)
{
  TFieldValue val = {.space = 0, .size = 0, .symbols = 0, .free = 0};
  int space = 0;

  for(int i = x + dx, j = y + dy; i >= 0 && j >= 0 && i < MAXX && j < MAXY; i += dx, j += dy) {
    if(pole[i][j] == symbol) {
      if(val.space < 2) {
        ++val.symbols;
        val.free = 0;
        if(val.space > 0) {
          space = 1;
        }
      }
      else {
        ++val.free;
      }
    }
    else if(pole[i][j] == NONA) {
      ++val.free;
      ++val.space;
    }
    else {
      break;
    }
    ++val.size;
  }

  val.space = space;
  if(val.symbols == 0) {
    val.space = 0;
  }
  val.free = val.free > 0;

  return val;
}


/*
 * secte hodnoty dvou TFieldValue a vrati
 */
TFieldValue sumValues(TFieldValue a, TFieldValue b)
{
  a.symbols += b.symbols;
  a.space += b.space;
  a.free += b.free;
  a.size += b.size;
  return a;
}


/*
 * prepocita namerena data na prioritu
 */
int realValue(TFieldValue v)
{
  //return 2 * v.symbols * v.symbols * (v.symbols + v.free) / (v.space+1) * !(v.size < TOKENS_TO_WIN - 1);
  return 2 * v.symbols * (v.symbols - v.space) * (v.symbols + v.free) * !(v.size < TOKENS_TO_WIN - 1);
}


/*
 * vypocet priority daneho pole pro dany znak
 */
int fieldValue(TGarray pole, int x, int y, int symbol)
{
  TFieldValue a, b, c, d, t;
  a = vsechnysmery(pole, x, y,  0,  1, symbol);
  t = vsechnysmery(pole, x, y,  0, -1, symbol); //shora dolu
  a = sumValues(a, t);

  b = vsechnysmery(pole, x, y,  1,  0, symbol);
  t = vsechnysmery(pole, x, y, -1,  0, symbol); //zleva doprava
  b = sumValues(b, t);

  c = vsechnysmery(pole, x, y, -1, -1, symbol);
  t = vsechnysmery(pole, x, y,  1,  1, symbol); //sikmo zprava doleva
  c = sumValues(c, t);

  d = vsechnysmery(pole, x, y, -1,  1, symbol);
  t = vsechnysmery(pole, x, y,  1, -1, symbol); //sikmo zleva doprava
  d = sumValues(d, t);

  return realValue(a) + realValue(b) + realValue(c) + realValue(d);
}


/*
 * hlavni funkce AI - vyhleda v poli nejlepsi tah a vrati souradnice
 *   pole - herni pole
 *   symbol - znacka hrace
 */
TCoord ai2(TGarray pole, int symbol)
{
  TCoord souradnice;
  TNode *stackX = NULL, *stackO = NULL;
  int maxX = 0, maxO = 0;
  int cX, cO;
  int stackXSize = 0, stackOSize = 0;
  
  for(int i = 0; i < MAXX; ++i) {
    for(int j = 0; j < MAXY; ++j) {
      if(pole[i][j] != NONA) {
        continue;
      }
      souradnice.x = i;
      souradnice.y = j;

      cX = fieldValue(pole, i, j, CROSS);
      if(cX > maxX) {
        maxX = cX;
        stackDrop(&stackX);
        stackXSize = 0;
        if(stackInsert(&stackX, souradnice)) {
          ++stackXSize;
        }
      }
      else if(cX == maxX) {
        if(stackInsert(&stackX, souradnice)) {
          ++stackXSize;
        }
      }

      cO = fieldValue(pole, i, j, CIRCLE);
      if(cO > maxO) {
        maxO = cO;
        stackDrop(&stackO);
        stackOSize = 0;
        if(stackInsert(&stackO, souradnice)) {
          ++stackOSize;
        }
      }
      else if(cO == maxO) {
        if(stackInsert(&stackO, souradnice)) {
          ++stackOSize;
        }
      }
    }
  }

  if(maxX == 0 && maxO == 0 && pole[MAXX/2][MAXY/2] == NONA)
  {
    souradnice.x = MAXX / 2;
    souradnice.y = MAXY / 2;
  }
  else if(maxX == maxO) {
    if(symbol == CROSS) {
      souradnice = stackGet(stackX, rand()%stackXSize);
    }
    else {
      souradnice = stackGet(stackO, rand()%stackOSize);
    }
  }
  else {
    if(maxX > maxO) {
      souradnice = stackGet(stackX, rand()%stackXSize);
    }
    else {
      souradnice = stackGet(stackO, rand()%stackOSize);
    }
  }

  stackDrop(&stackX);
  stackDrop(&stackO);

  return souradnice;
}
