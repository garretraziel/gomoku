/*
 *  GOMOKU - universal engine for competiting AIs in five-in-a-row
 *
 *  Made by Jan Sedlák (Garret Raziel), 2009
 *
 *  Released under GNU/GPL licencion
 *
 *
 *
 *
 */
#include "core.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

/*int* game()
{
    GARRAY game_board;
    ai1 player1; ai2 player2;
    int turns=0;

    clear_board(game_board);
    write_field(game_board);

    while (true)
    {
        DIRECTIONS dir;
        GARRAY game_board_safe;
        copy_array(game_board,game_board_safe);
        dir = player1.play(game_board_safe);
        if (game_board[dir.x][dir.y]!=NONA)
            {
                cout << "AI1 is a cheater and lost the game!";
                break;
            }
        game_board[dir.x][dir.y]=CROSS;
        turns++;
        if (check_win(game_board, CROSS)) {
            cout << "AI1 has won the game.\n";
            break;
        }
        copy_array(game_board,game_board_safe);
        dir = player2.play(game_board_safe);
        if (game_board[dir.x][dir.y]!=NONA)
            {
                cout << "AI2 is a cheater and lost the game!";
                break;
            }
        game_board[dir.x][dir.y]=CIRCLE;
        turns++;
        if (check_win(game_board, CIRCLE)) {
            cout << "AI2 has won the game.\n";
            break;
        }
    }

    cout << "Game ended after " << turns << " turns.\n";
    return 0;
};*/

void clear_board(GARRAY &game_board)
{
    for (int i=0;i<MAXX;i++)
        for (int j=0;j<MAXY;j++)
            game_board[i][j]=NONA;
}

void write_field(GARRAY game_board)
{
    for (int i=0;i<MAXX;i++)
    {
        for (int j=0;j<MAXY;j++)
            cerr << game_board[i][j];
        cerr << endl;
    }
    cerr << endl << endl << endl;
}

bool check_rec(GARRAY game_board, int x, int y, int direction, int count, int token) //--fucking UNGLY recursive function, hope that will work
{
    if ((game_board[x][y]==token)&&((count+1)==TOKENS_TO_WIN)) return true;
    else if (game_board[x][y]!=token) return false;
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
    else return false;
    return false;
}

bool check_win(GARRAY game_board, int token)
{
    bool win=false;
    for (int j=0;j<MAXY;j++)
        for (int i=0;i<MAXX;i++)
        {
            if ((game_board[i][j]!=NONA)&&(game_board[i][j]==token))
            {
                int count=0;
                if (check_rec(game_board,i,j,1,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,2,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,3,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,4,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,5,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,6,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,7,count,game_board[i][j])==true) {win=true; break;}
                count=0;
                if (check_rec(game_board,i,j,8,count,game_board[i][j])==true) {win=true; break;}
            }
        }
    return win;
};

void copy_array(GARRAY ar1, GARRAY ar2)
{
    for (int i=0;i<MAXX;i++)
        for (int j=0;j<MAXY;j++)
            ar2[i][j]=ar1[i][j];
};
