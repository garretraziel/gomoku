#ifndef DEFINES_H_
#define DEFINES_H_

#define MAXX 15
#define MAXY 15

typedef int GARRAY[MAXX][MAXY];

#define TOKENS_TO_WIN 5

#define CROSS 1
#define NONA 0
#define CIRCLE 2

#define WHITE 0xffffffff
#define RED 0xff0000ff
#define BLACK 0x000000ff
#define YELLOW 0xffff00ff
#define PURPLE 0xff00ffff
#define BLUE 0x00ffffff
#define GREEN 0x00ff00ff

#define BLACK_PAPER 0x00000088

struct DIRECTIONS
    {
        int x;
        int y;
    };

/* Directions:
 *
 * _________
 *|1   2   3|
 *|         |
 *|4       5|
 *|         |
 *|6   7   8|
 *-----------
 *
 *
 *
 */

#endif
