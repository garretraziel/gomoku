#ifndef DEFINES_H__
#define DEFINES_H__

// velikost hraciho pole
#define MAXX 20 // radky
#define MAXY 15 // sloupce

// hraci pole
typedef int TGarray[MAXX][MAXY];

// struktura reprezentujici souradnice tahu
typedef struct {
  int x, y;
} TCoord;

// ukazatel na herni funkci
typedef TCoord(*TPlayer)(TGarray, int);

// pocet potrebnych znacek k vyhre
#define TOKENS_TO_WIN 5

/*
#define NONA   0
#define CROSS  1
#define CIRCLE 2
*/
// vycet moznych symbolu, nic, krizek nebo kolecko
typedef enum {
  NONA, CROSS, CIRCLE
} TSymbol;

typedef enum {
  EXIT, RESTART, MENU
} TAction;

// definice velikosti jednoho policka a sirky statusbaru
#define FIELD_SIZE  32 // 16
#define STATUSBAR_SIZE 16

// definice nekolika barev
#define WHITE 0xffffffff
#define RED 0xff0000ff
#define BLACK 0x00000000
#define YELLOW 0xffff00ff
#define PURPLE 0xff00ffff
#define BLUE 0x00ffffff
#define GREEN 0x00ff00ff

#endif
