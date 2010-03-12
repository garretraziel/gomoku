#include <stdlib.h>
#include "defines.h"

int turns=0;

int mysymbol;
int othersymbol;

int check_rec_a(GARRAY game_board, int x, int y, int direction, int* count, int token, int count_to_win)
{
	if ((game_board[x][y]==token)&&(((*count)+1)==count_to_win)) return 1;
    else if (game_board[x][y]!=token) return 0;
    else if ((game_board[x][y]==token)&&(((*count)+1)<count_to_win))
    {
        //cerr << "rec\n";
        (*count)++;
        if ((direction==1)&&((x>=1)&&(y>=1))) return check_rec_a(game_board, x-1, y-1, 1, count,token,count_to_win);
        else if ((direction==2)&&(y>=1)) return check_rec_a(game_board, x, y-1, 2, count,token,count_to_win);
        else if ((direction==3)&&((y>=1)&&(x<(MAXX-1)))) return check_rec_a(game_board, x+1, y-1, 3, count,token,count_to_win);
        else if ((direction==4)&&(x>=1)) return check_rec_a(game_board, x-1, y, 4, count,token,count_to_win);
        else if ((direction==5)&&(x<(MAXX-1))) return check_rec_a(game_board, x+1, y, 5, count,token,count_to_win);
        else if ((direction==6)&&((x>=1)&&(y<(MAXY-1)))) return check_rec_a(game_board, x-1, y+1, 6, count,token,count_to_win);
        else if ((direction==7)&&(y<(MAXY-1))) return check_rec_a(game_board, x, y+1, 7, count,token,count_to_win);
        else if ((direction==8)&&((x<(MAXX-1))&&(y<(MAXY-1)))) return check_rec_a(game_board, x+1, y+1, 8, count,token,count_to_win);
    }
    else return 0;
    return 0;
}

int check_win_a(GARRAY game_board, int token, int count_to_win)
{
	int win=0;
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
        {
            if ((game_board[i][j]!=NONA)&&(game_board[i][j]==token))
            {
                int count=0;
                if (check_rec_a(game_board,i,j,1,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,2,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,3,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,4,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,5,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,6,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,7,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
                count=0;
                if (check_rec_a(game_board,i,j,8,&count,game_board[i][j],count_to_win)==1) {win=1; break;}
            }
        }
    return win;
}

int check_act(GARRAY game_board, int token, int i, int j, int towin)
{
    int count, count2=0;
    if (check_rec_a(game_board,i,j,1,&count,token,towin-1)==1) {return 1;}
    if (check_rec_a(game_board,i,j,8,&count2,token,towin-1)==1) {return 1;}
    if ((count+count2-1)==towin-1) return 1;
    count = count2 = 0;
    if (check_rec_a(game_board,i,j,2,&count,token,towin-1)==1) {return 1;}
    if (check_rec_a(game_board,i,j,7,&count2,token,towin-1)==1) {return 1;}
    if ((count+count2-1)==towin-1) return 1;
    count = count2 = 0;
    if (check_rec_a(game_board,i,j,3,&count,token,towin-1)==1) {return 1;}
    if (check_rec_a(game_board,i,j,6,&count2,token,towin-1)==1) {return 1;}
    if ((count+count2-1)==towin-1) return 1;
    count = count2 = 0;
    if (check_rec_a(game_board,i,j,4,&count,token,towin-1)==1) {return 1;}
    if (check_rec_a(game_board,i,j,5,&count2,token,towin-1)==1) {return 1;}
    if ((count+count2-1)==towin-1) return 1;
    count = count2 = 0;
    return 0;
}

int testmode(GARRAY array, int token, int pos)
{
	//if (token==othersymbol)//TODO: toto taky jeste neni uplne idealni
    //{
     //for (int j=MAXY-1;j>=0;j--)
        //for (int i=MAXX-1;i>=0;i--)
		//{
			//if (array[i][j]==NONA) {
				//array[i][j]=othersymbol;
				//if (check_act(array,othersymbol,i,j,pos)==1) return 1;
				//array[i][j]=NONA;
			//}
        //}
    //}
    //else if (token==mysymbol)//TODO:Toto jeste neni uplne ideal
    //{
     //for (int j=MAXY-1;j>=0;j--)
        //for (int i=MAXX-1;i>=0;i--)
		//{
			//if (array[i][j]==NONA) {
				//array[i][j]=mysymbol;
				//if (check_act(array,othersymbol,i,j,pos)==1) if (pos==TOKENS_TO_WIN) return 1; else pos++;
				//else array[i][j]=NONA;
			//}
        //}
    //}
    //return 0;
    return 1;
}

coord ai1(GARRAY game_board, int symbol)
{
  coord dir;
    GARRAY array;
    mysymbol=symbol;
    if (symbol==CROSS) othersymbol=CIRCLE;
    else othersymbol=CROSS;
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
			array[i][j]=game_board[i][j];
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
		{
			if (array[i][j]==NONA) {
				array[i][j]=mysymbol;
				if (check_win_a(array,mysymbol,TOKENS_TO_WIN)==1) {dir.x=i; dir.y=j; return dir;}
				array[i][j]=NONA;
			}
		}
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
		{
			if (array[i][j]==NONA) {
				array[i][j]=othersymbol;
				if (check_win_a(array,othersymbol,TOKENS_TO_WIN)==1) {dir.x=i; dir.y=j; return dir;}
				array[i][j]=NONA;
			}
		}
    //if (turns==1) {game_board[MAXX/2][MAXY/2]=mysymbol; return true;}
    for (int j=MAXY-1;j>=0;j--)
        for (int i=MAXX-1;i>=0;i--)
		{
			if (array[i][j]==NONA) {
				array[i][j]=othersymbol;
                if (check_act(array,othersymbol,i,j,TOKENS_TO_WIN)==1) if (testmode(array,othersymbol,TOKENS_TO_WIN-1)) {dir.x=i; dir.y=j; return dir;}
				array[i][j]=NONA;
			}
		}
	for (int f=TOKENS_TO_WIN; f>2 ;f--)
		{
		    for (int j=0;j<MAXY;j++)
                for (int i=0;i<MAXX;i++)
				{
					if (array[i][j]==NONA) {
						array[i][j]=mysymbol;
                        if (check_act(array,mysymbol,i,j,f)==1) /*if (testmode(array,mysymbol,f))*/ {dir.x=i; dir.y=j; return dir;}
						array[i][j]=NONA;
					}
				}
		}
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
		{
			if ((array[i-1][j-1]==othersymbol)&&((i>=1)&&(j>=1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i-1][j]==othersymbol)&&(i>=1)&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i+1][j-1]==othersymbol)&&((i<(MAXX-1))&&(j>=1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i][j-1]==othersymbol)&&(j>=1)&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i][j+1]==othersymbol)&&(j<(MAXY-1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i+1][j]==othersymbol)&&(i<(MAXX-1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i-1][j+1]==othersymbol)&&((i>=1)&&(j<(MAXY-1)))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i+1][j+1]==othersymbol)&&((i<(MAXX-1))&&(j<(MAXY-1)))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
		}
  return dir;
}
