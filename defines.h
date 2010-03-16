#ifndef DEFINES_H__
#define DEFINES_H__

#define MAXX 15
#define MAXY 15

typedef int TGarray[MAXY][MAXX];

typedef struct {
  int x, y;
} TCoord;

typedef TCoord(*TPlayer)(TGarray, int);

#define TOKENS_TO_WIN 5

#define NONA   0
#define CROSS  1
#define CIRCLE 2

#define FIELD_SIZE  32 // 16
#define STATUSBAR_SIZE 16

#define WHITE 0xffffffff
#define RED 0xff0000ff
#define BLACK 0x00000000
#define YELLOW 0xffff00ff
#define PURPLE 0xff00ffff
#define BLUE 0x00ffffff
#define GREEN 0x00ff00ff

#endif
