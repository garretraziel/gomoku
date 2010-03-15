#ifndef DEFINES_H_
#define DEFINES_H_

#define MAXX 15
#define MAXY 15

typedef int GARRAY[MAXX][MAXY];

typedef struct {
  int x, y;
} coord;

typedef coord(*PLAYER)(GARRAY, int);

/*typedef struct {
  int player1, player2;
} player_list;*/

#define TOKENS_TO_WIN 5

#define NONA   0
#define CROSS  1
#define CIRCLE 2

#define SIZE_  32 // 16

#define WHITE 0xffffffff
#define RED 0xff0000ff
#define BLACK 0x00000000
#define YELLOW 0xffff00ff
#define PURPLE 0xff00ffff
#define BLUE 0x00ffffff
#define GREEN 0x00ff00ff

#endif
