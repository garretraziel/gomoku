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

#endif
