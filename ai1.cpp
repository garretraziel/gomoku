#include "ai1.h"

ai1::~ai1()
{
    //dtor
}

bool ai1::testmode(GARRAY array, int token, int pos)
{
    if (token==CROSS)
    {
     for (int j=MAXY-1;j>=0;j--)
        for (int i=MAXX-1;i>=0;i--)
		{
			if (array[i][j]==NONA) {
				array[i][j]=CROSS;
				if (check_act(array,CROSS,i,j,pos)==true) return true;
				array[i][j]=NONA;
			}
        }
    }
    else if (token==CIRCLE)//TODO:Toto jeste neni uplne ideal
    {
     for (int j=MAXY-1;j>=0;j--)
        for (int i=MAXX-1;i>=0;i--)
		{
			if (array[i][j]==NONA) {
				array[i][j]=CIRCLE;
				if (check_act(array,CROSS,i,j,pos)==true) if (pos==TOKENS_TO_WIN) return true; else pos++;
				else array[i][j]=NONA;
			}
        }
    }
    return false;
}

DIRECTIONS ai1::play(GARRAY &game_board)
{
    //HERE past what must to be hapen when it's your turn
    // function uses GARRAY, which is array 0-MAXX and 0-MAXY (both 15 by default) of integer
    // const CIRCLE from defines.h represent circle (and it is number 2 by default), CROSS (1 by def)
    // represent cross token and NONA (0 by def) represent empty field
    //
    // function returns true if all have been done well and false if there was some errors
    //
    // IT IS FORBIDDEN TO CHANGE ALREADY PLACED TOKENS!
    DIRECTIONS dir;
    GARRAY array;
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
			array[i][j]=game_board[i][j];
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
		{
			if (array[i][j]==NONA) {
				array[i][j]=CIRCLE;
				if (check_win(array,CIRCLE)==true) {dir.x=i; dir.y=j; return dir;}
				array[i][j]=NONA;
			}
		}
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
		{
			if (array[i][j]==NONA) {
				array[i][j]=CROSS;
				if (check_win(array,CROSS)==true) {dir.x=i; dir.y=j; return dir;}
				array[i][j]=NONA;
			}
		}
    //if (turns==1) {game_board[MAXX/2][MAXY/2]=CIRCLE; return true;}
    for (int j=MAXY-1;j>=0;j--)
        for (int i=MAXX-1;i>=0;i--)
		{
			if (array[i][j]==NONA) {
				array[i][j]=CROSS;
//				int count=0;
//				if (check_rec(array,i,j,1,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,2,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,3,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,4,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,5,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,6,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,7,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				count=0;
//				if (check_rec(array,i,j,8,count,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}
//				if (check_win(array,CROSS,TOKENS_TO_WIN-1)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)==true) {dir.x=i; dir.y=j; return dir;}//TODO: Upravit zpusobem "Zahrnuta poloha i,j"
                if (check_act(array,CROSS,i,j)==true) if (testmode(array,CROSS,TOKENS_TO_WIN-1)) {dir.x=i; dir.y=j; return dir;}
				array[i][j]=NONA;
			}
		}
	for (int f=TOKENS_TO_WIN; f>2 ;f--)
		{
		    for (int j=0;j<MAXY;j++)
                for (int i=0;i<MAXX;i++)
				{
					if (array[i][j]==NONA) {
						array[i][j]=CIRCLE;
//						int count=0;
//						if (check_rec(array,i,j,1,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,2,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,3,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,4,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,5,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,6,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,7,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
//						count=0;
//						if (check_rec(array,i,j,8,count,array[i][j],f)==true) {dir.x=i; dir.y=j; return dir;}
                        if (check_act(array,CIRCLE,i,j,f)==true) /*if (testmode(array,CIRCLE,f))*/ {dir.x=i; dir.y=j; return dir;}
						array[i][j]=NONA;
					}
				}
		}
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
		{
			if ((array[i-1][j-1]==CROSS)&&((i>=1)&&(j>=1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i-1][j]==CROSS)&&(i>=1)&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i+1][j-1]==CROSS)&&((i<(MAXX-1))&&(j>=1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i][j-1]==CROSS)&&(j>=1)&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i][j+1]==CROSS)&&(j<(MAXY-1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i+1][j]==CROSS)&&(i<(MAXX-1))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i-1][j+1]==CROSS)&&((i>=1)&&(j<(MAXY-1)))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
			else if ((array[i+1][j+1]==CROSS)&&((i<(MAXX-1))&&(j<(MAXY-1)))&&(array[i][j]==NONA)) {dir.x=i; dir.y=j; return dir;}
		}
    return dir;
};

bool ai1::check_rec(GARRAY game_board, int x, int y, int direction, int &count, int token, int count_to_win) //--fucking UNGLY recursive function, hope that will work
{
    if ((game_board[x][y]==token)&&((count+1)==count_to_win)) return true;
    else if (game_board[x][y]!=token) return false;
    else if ((game_board[x][y]==token)&&((count+1)<count_to_win))
    {
        //cerr << "rec\n";
        count++;
        if ((direction==1)&&((x>=1)&&(y>=1))) return check_rec(game_board, x-1, y-1, 1, count,token,count_to_win);
        else if ((direction==2)&&(y>=1)) return check_rec(game_board, x, y-1, 2, count,token,count_to_win);
        else if ((direction==3)&&((y>=1)&&(x<(MAXX-1)))) return check_rec(game_board, x+1, y-1, 3, count,token,count_to_win);
        else if ((direction==4)&&(x>=1)) return check_rec(game_board, x-1, y, 4, count,token,count_to_win);
        else if ((direction==5)&&(x<(MAXX-1))) return check_rec(game_board, x+1, y, 5, count,token,count_to_win);
        else if ((direction==6)&&((x>=1)&&(y<(MAXY-1)))) return check_rec(game_board, x-1, y+1, 6, count,token,count_to_win);
        else if ((direction==7)&&(y<(MAXY-1))) return check_rec(game_board, x, y+1, 7, count,token,count_to_win);
        else if ((direction==8)&&((x<(MAXX-1))&&(y<(MAXY-1)))) return check_rec(game_board, x+1, y+1, 8, count,token,count_to_win);
    }
    else return false;
    return false;
}

bool ai1::check_win(GARRAY game_board, int token, int count_to_win)
{
    bool win=false;
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
        {
            if ((game_board[i][j]!=NONA)&&(game_board[i][j]==token))
            {
                int count=0;
                if (check_rec(game_board,i,j,1,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,2,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,3,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,4,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,5,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,6,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,7,count,game_board[i][j],count_to_win)==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,8,count,game_board[i][j],count_to_win)==true) {win=true; break;}
            }
        }
    return win;
};

bool ai1::check_act(GARRAY game_board, int token, int i, int j, int towin)
{
    int count, count2=0;
    if (check_rec(game_board,i,j,1,count,token,towin-1)==true) {return true;}
    if (check_rec(game_board,i,j,8,count2,token,towin-1)==true) {return true;}
    if ((count+count2-1)==towin-1) return true;
    count = count2 = 0;
    if (check_rec(game_board,i,j,2,count,token,towin-1)==true) {return true;}
    if (check_rec(game_board,i,j,7,count2,token,towin-1)==true) {return true;}
    if ((count+count2-1)==towin-1) return true;
    count = count2 = 0;
    if (check_rec(game_board,i,j,3,count,token,towin-1)==true) {return true;}
    if (check_rec(game_board,i,j,6,count2,token,towin-1)==true) {return true;}
    if ((count+count2-1)==towin-1) return true;
    count = count2 = 0;
    if (check_rec(game_board,i,j,4,count,token,towin-1)==true) {return true;}
    if (check_rec(game_board,i,j,5,count2,token,towin-1)==true) {return true;}
    if ((count+count2-1)==towin-1) return true;
    count = count2 = 0;
    return false;
};
