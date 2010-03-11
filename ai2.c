#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

typedef struct {
  int symbols; // kolik mam znacek
  int size;    // celkova velikost znaku + mezer
  int space;   // zda je tam mezera
  int free;    // zda je konec volny
} TFieldValue;



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
  x.space = a.space || b.space;
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
  coord maxs;
  int c, ccross, ccircle;
  int maxc = 0, p;
  
  for(int i = 0; i < MAXX; ++i) {
    for(int j = 0; j < MAXY; ++j) {
      if(papir[i][j] != NONA) {
        continue;
      }


      ccross = fieldValue(papir, i, j, CROSS);
//      if(ccross > 0)
//        printf("  X[%2d,%2d]%d \n", i,j,ccross);
      ccircle = fieldValue(papir, i, j, CIRCLE);
//      if(ccircle > 0)
//        printf("  O[%2d,%2d]%d \n", i,j,ccircle);

//      c = (ccross > ccircle) ? ccross + ccircle / 4 : ccircle + ccross / 4;
      c = (ccross > ccircle) ? ccross : ccircle;
      if(c > maxc) {
        maxc = c;
        maxs.x = i;
        maxs.y = j;
        p = 1;
      }
      else if(c == maxc) {
        ++p;
      }
    }
  }

  if(maxc == 0) // pokud neni tah, tak stred
  {
    maxs.x = MAXX / 2;
    maxs.y = MAXY / 2;
  }

//  printf("#%d \n", p);
//  putchar('\n');
//  putchar('\n');
  return maxs;
}

// mel by se vybrat nejdulezitejsi duvod, proc nekde hrat, ostatni by mely byt jen jako bonus pro pripdadne rozhodovani
// X_._X je hodnoceno prilis dobre - scitat i mezery? jo
