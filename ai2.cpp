#include <iostream>
#include <cstdlib>

#include "ai2.h"
#include "defines.h"

// option:
//

class option
{
  public:
    option(coord);
    ~option() {}
    
    coord value;
    option* next;
};


// stack:
//

class stack
{
  public:
    stack();
    ~stack();

    int pop(); // remove
    int push(coord, int); // add
    bool empty(option *);
    coord random(int);

  private:
    option *krizky, *kolecka;
    int krizku, kolecek;

    int pop(option **);
};


// ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

// option:
//


option::option(coord c)
{
  value = c;
  next = NULL;
}


// stack:
// 

stack::stack()
{
  krizky = NULL;
  kolecka = NULL;
  krizku = kolecek = 0;
}

stack::~stack()
{
  this->pop();
}

int stack::push(coord c, int ply)
{
  option *newroot = new option(c);

  if(ply == CROSS)
  {
    newroot->next = krizky;
    krizky = newroot;
    krizku++;
  }
  else
  {
    newroot->next = kolecka;
    kolecka = newroot;
    kolecek++;
  }

  return 0;
}

int stack::pop()
{
  this->pop(&kolecka);
  this->pop(&krizky);
  krizku = kolecek = 0;
  return 0;
}

int stack::pop(option **root)
{
  option *t;
  while(*root != NULL)
  {
    t = (*root)->next;
    delete *root;
    *root = t;
  }
  return 0;
}

coord stack::random(int me)
{
  int a, i;
  option *o;

  if((me == CROSS && !empty(krizky)) || (me == CIRCLE && empty(kolecka)))
  {
    a = rand() % krizku;
    o = krizky;
  }
  else
  {
    a = rand() % kolecek;
    o = kolecka;
  }

  for(i = 0; i < a; ++i)
    o = o->next;

  return o->value;
}

bool stack::empty(option *root)
{
  return root == NULL;
}


// ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

// AgImo:
//

int AgImo::count_value(GARRAY pole, int x, int y, int p, int &c, int &k, int &s)
{
  if(pole[x][y] == p && s <= 1)
  {
    c += 1;
    if(s == 1)
      k = 1;
  }
  else if(pole[x][y] == NONA || pole[x][y] == p)
  {
    s += 1;
    if(s == 2 && (s = 1))
      return 0;
  }
  else
    return 0;

  return 1;
}


int AgImo::doprava(GARRAY pole, int x, int y, int p)
{
  int i, c = 0, s = 0, k = 0;
  for(i = y + 1; i < MAXY; ++i)
    if(!count_value(pole, x, i, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::doleva(GARRAY pole, int x, int y, int p)
{
  int i, c = 0, s = 0, k = 0;
  for(i = y - 1; i >= 0; --i)
    if(!count_value(pole, x, i, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::nahoru(GARRAY pole, int x, int y, int p)
{
  int i, c = 0, s = 0, k = 0;
  for(i = x - 1; i >= 0; --i)
    if(!count_value(pole, i, y, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::dolu(GARRAY pole, int x, int y, int p)
{
  int i, c = 0, s = 0, k = 0;
  for(i = x + 1; i < MAXX; ++i)
    if(!count_value(pole, i, y, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::vlevonahoru(GARRAY pole, int x, int y, int p)
{
  int i, j, c = 0, s = 0, k = 0;
  for(i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
    if(!count_value(pole, i, j, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::vpravonahoru(GARRAY pole, int x, int y, int p)
{
  int i, j, c = 0, s = 0, k = 0;
  for(i = x - 1, j = y + 1; i >= 0 && j < MAXY; --i, ++j)
    if(!count_value(pole, i, j, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::vlevodolu(GARRAY pole, int x, int y, int p)
{
  int i, j, c = 0, s = 0, k = 0;
  for(i = x + 1, j = y - 1; i < MAXX && j >= 0; ++i, --j)
    if(!count_value(pole, i, j, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}

int AgImo::vpravodolu(GARRAY pole, int x, int y, int p)
{
  int i, j, c = 0, s = 0, k = 0;
  for(i = x + 1, j = y + 1; i < MAXX && j < MAXY; ++i, ++j)
    if(!count_value(pole, i, j, p, c, k, s))
      break;
  return ((c * 10) + k) * 10 + s - k;
}


int AgImo::check_cell(GARRAY papir, int x, int y, int w)
{
  int c = 0;
  int s = 0;
  int k;

  c = doleva(papir, x, y, w) + doprava(papir, x, y, w);
  if(c % 10 == 0)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s = (c - 1) * (c - 1) * (c - k);
  }
  else if(c % 10 == 1)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s = (c - 1) * c * (c - k);
  }
  else
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s = c * c * (c - k);
  }

  c = nahoru(papir, x, y, w)  + dolu(papir, x, y, w);
  if(c % 10 == 0)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += (c - 1) * (c - 1) * (c - k);
  }
  else if(c % 10 == 1)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += (c - 1) * c * (c - k);
  }
  else
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += c * c * (c - k);
  }
 
  c = vlevodolu(papir, x, y, w) + vpravonahoru(papir, x, y, w);
  if(c % 10 == 0)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += (c - 1) * (c - 1) * (c - k);
  }
  else if(c % 10 == 1)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += (c - 1) * c * (c - k);
  }
  else
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += c * c * (c - k);
  }
  
  c = vlevonahoru(papir, x, y, w) + vpravodolu(papir, x, y, w);
  if(c % 10 == 0)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += (c - 1) * (c - 1) * (c - k);
  }
  else if(c % 10 == 1)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += (c - 1) * c * (c - k);
  }
  else
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s += c * c * (c - k);
  }
  
  return s;
}

// vychytat prioritnejsi hrani tam, kde je volne misto - OK
//
// nizsi snizeni priority rad s mezerou
// 
// snizeni priority oemezenych rad v zavislosti na delce a tedy i potrebnem volnem miste
// 
// postavit si vlastni neomezeny 3 by melo byt vic, nez blokovat uz z jedny strany blokovanou 3 soupere


/* puvodni hodnoceni
  return (c - k) * 10 + s - k;

  if(c % 10 == 0)
  {
    c = c / 10;
    s = (c - 1) * (c - 1) * c;
  }
  else if(c % 10 == 1)
  {
    c = c / 10;
    s = (c - 1) * c * c;
  }
  else
  {
    c = c / 10;
    s = c * c * c;
  }
*/

/* nove, nefunguje
  return ((c * 10) + k) * 10 + s - k;


  if(c % 10 == 0)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s = (c - 1) * (c - 1) * (c - k / 2);
  }
  else if(c % 10 == 1)
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s = (c - 1) * c * (c - k / 2);
  }
  else
  {
    c /= 10;
    k = c % 10;
    c /= 10;
    s = c * c * (c - k / 2);
  }
*/

coord AgImo::check_array(GARRAY papir, int me, int difficulty)
{
  coord s;
  int i, j, c, ccross, ccircle;
  int maxc = 0;

  stack *zasobnik = new stack();
  
  for(i = 0; i < MAXX; ++i)
  {
    for(j = 0; j < MAXY; ++j)
    {
      if(papir[i][j] != NONA)
        continue;
      
      ccross = check_cell(papir, i, j, CROSS);
      ccircle = check_cell(papir, i, j, CIRCLE);
   
      c = (ccross > ccircle) ? ccross + ccircle / 2 : ccircle + ccross / 2;

      if(c > maxc)
      {
        s.x = i;
        s.y = j;
        maxc = c;
        zasobnik->pop();
        if(ccross == ccircle)
          zasobnik->push(s, me);
        else
          zasobnik->push(s, (ccross > ccircle) ? CROSS : CIRCLE);
      }
      else if(c == maxc)
      {
        s.x = i;
        s.y = j;
        if(ccross == ccircle)
          zasobnik->push(s, me);
        else
          zasobnik->push(s, (ccross > ccircle) ? CROSS : CIRCLE);
      }
    }
  }

  if(maxc == 0)
  {
    s.x = MAXX / 2 + me;
    s.y = MAXY / 2 + me;
    if(papir[s.x][s.y] != NONA)
      s = zasobnik->random(me);
  }
  else
    s = zasobnik->random(me);

  delete zasobnik;

  return s;
}



ai2::ai2()
{
    //ctor
}

ai2::~ai2()
{
    //dtor
}

coord ai2::play(GARRAY &game_board, int symbol, int difficulty)
{
  return check_array(game_board, symbol, difficulty);
}
