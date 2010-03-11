#include "defines.h"


// vyprazdneni pole OK
void clearBoard(GARRAY game_board)
{
  for (int i = 0; i < MAXX; i++)
    for (int j = 0; j < MAXY; j++)
      game_board[i][j] = NONA;
}


// tohle pujde pryc
int check_rec(GARRAY game_board, int x, int y, int direction, int count, int token) //--fucking UNGLY recursive function, hope that will work
{
    if ((game_board[x][y]==token)&&((count+1)==TOKENS_TO_WIN)) return 1;
    else if (game_board[x][y]!=token) return 0;
    else if ((game_board[x][y]==token)&&((count+1)<TOKENS_TO_WIN))
    {
        //cerr << "rec\n";
        count++;
        if ((direction==1)&&((x>=1)&&(y>=1))) return check_rec(game_board, x-1, y-1, 1, count,token);
        else if ((direction==2)&&(y>=1)) return check_rec(game_board, x, y-1, 2, count,token);
        else if ((direction==3)&&((y>=1)&&(x<(MAXX-1)))) return check_rec(game_board, x+1, y-1, 3, count,token);
        else if ((direction==4)&&(x>=1)) return check_rec(game_board, x-1, y, 4, count,token);
        else if ((direction==5)&&(x<(MAXX-1))) return check_rec(game_board, x+1, y, 5, count,token);
        else if ((direction==6)&&((x>=1)&&(y<(MAXY-1)))) return check_rec(game_board, x-1, y+1, 6, count,token);
        else if ((direction==7)&&(y<(MAXY-1))) return check_rec(game_board, x, y+1, 7, count,token);
        else if ((direction==8)&&((x<(MAXX-4))&&(y<(MAXY-1)))) return check_rec(game_board, x+1, y+1, 8, count,token);
    }
    else return 0;
    return 0;
}


// taky pujde pryc
int check_win(GARRAY game_board, int token)
{
    int win=0;
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
        {
            if ((game_board[i][j]!=NONA)&&(game_board[i][j]==token))
            {
                int count=0;
                if (check_rec(game_board,i,j,1,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,2,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,3,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,4,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,5,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,6,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,7,count,game_board[i][j])==1) {win=1; break;}
                count=0;
                if (check_rec(game_board,i,j,8,count,game_board[i][j])==1) {win=1; break;}
            }
        }
    return win;
}


// kontrola, zda je tah vyherni
int checkWin(GARRAY game_board, coord souradnice)
{
  // TODO: napsat znovu a lip
  return check_win(game_board, game_board[souradnice.x][souradnice.y]);
}


// vola herni funkci a vraci souradnice, pokud jsou v poradku
coord play(GARRAY game_board, PLAYER player, int symbol)
{
  coord c;

  // TODO: pokud se nekdo snazi hrat kam nema, co se bude dit? ted je loop, ja bych ho dal pryc aukoncil hru
//  while(1)
//  {
    c = player(game_board, symbol);
    if(c.x >= 0 && c.x < MAXX && c.y >= 0 && c.y < MAXY && game_board[c.x][c.y] == NONA ) {
      return c;
    }
//  }
  return c;
}
