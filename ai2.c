#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

typedef struct {
  int symbols; // kolik mam znacek
  int size;    // celkova velikost znaku + mezer
  int space;   // zda je tam mezera
  int free;    // zda je konec volny
} TFieldValue;



typedef struct node {
  coord val;
  struct node *next;
} TNode;

// vlozeni prvku do zasobniku
int stackInsert(TNode **root, coord val)
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

// smazani celeho zasobniku
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

// vyhledani n-teho prvku ze zasobniku
coord stackGet(TNode *root, int n)
{
  if(n > 0) {
    return stackGet(root->next, n-1);
  }
  return root->val;
}




// vypocita pocet danych znaku v rade, pocet mezer, ktere se tam vyskutuji a delku volneho mista
TFieldValue vsechnysmery(GARRAY pole, int x, int y, int dx, int dy, int symbol)
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


// scita dva TFieldValue
TFieldValue sumValues(TFieldValue a, TFieldValue b)
{
  TFieldValue x;
  x.symbols = a.symbols + b.symbols;
//  x.space = a.space || b.space;
  x.space = a.space + b.space;
  x.free = a.free + b.free;
  x.size = a.size + b.size;
  return x;
}


// prepocita namerena data na prioritu
int realValue(TFieldValue v)
{
  //return 2 * v.symbols * v.symbols * (v.symbols + v.free) / (v.space+1) * !(v.size < TOKENS_TO_WIN - 1);
  return 2 * v.symbols * (v.symbols - v.space) * (v.symbols + v.free) * !(v.size < TOKENS_TO_WIN - 1);
}


// vypocet priority daneho pole pro dany znak
int fieldValue(GARRAY pole, int x, int y, int symbol)
{
  TFieldValue a, b, c, d, t;
  a = vsechnysmery(pole, x, y,  0,  1, symbol);
  t = vsechnysmery(pole, x, y,  0, -1, symbol); //shora dolu
  a = sumValues(a, t);

  b = vsechnysmery(pole, x, y,  1,  0, symbol);
  t = vsechnysmery(pole, x, y, -1,  0, symbol); //zleva doprava
  b = sumValues(b, t);

  c = vsechnysmery(pole, x, y, -1, -1, symbol);
  t = vsechnysmery(pole, x, y,  1,  1, symbol); //sikmo zp doleva
  c = sumValues(c, t);

  d = vsechnysmery(pole, x, y, -1,  1, symbol);
  t = vsechnysmery(pole, x, y,  1, -1, symbol); //sikmo zl doprava
  d = sumValues(d, t);

  return realValue(a) + realValue(b) + realValue(c) + realValue(d);
}


// vyhleda v poli nejlepsi tah a hraje
coord ai2(GARRAY papir, int me)
{
  coord souradnice;
  TNode *stackX = NULL, *stackO = NULL;
  int maxX = 0, maxO = 0;
  int cX, cO;
  int stackXSize = 0, stackOSize = 0;
  
  for(int i = 0; i < MAXX; ++i) {
    for(int j = 0; j < MAXY; ++j) {
      if(papir[i][j] != NONA) {
        continue;
      }
      souradnice.x = i;
      souradnice.y = j;

      cX = fieldValue(papir, i, j, CROSS);
      if(cX > maxX) {
        maxX = cX;
        stackDrop(&stackX);
        stackInsert(&stackX, souradnice);
        stackXSize = 1;
      }
      else if(cX == maxX) {
        stackInsert(&stackX, souradnice);
        ++stackXSize;
      }

      cO = fieldValue(papir, i, j, CIRCLE);
      if(cO > maxO) {
        maxO = cO;
        stackDrop(&stackO);
        stackInsert(&stackO, souradnice);
        stackOSize = 1;
      }
      else if(cO == maxO) {
        stackInsert(&stackO, souradnice);
        ++stackOSize;
      }
    }
  }

  if(maxX == 0 && maxO == 0 && papir[MAXX/2][MAXY/2] == NONA) // pokud neni poradny tah, tak stred, pokud je volny
  {
    souradnice.x = MAXX / 2;
    souradnice.y = MAXY / 2;
  }
  else if(maxX == maxO) {
    if(me == CROSS) {
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

//  printf("X%d O%d \n", stackXSize, stackOSize);

  return souradnice;
}
// komentar pro test gitu
