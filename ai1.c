/*
 * (c) Garret Raziel and Alda (2010)
 * released under GNU/GPL v.3,
 * for further details, see LICENCE
 */

#include <stdlib.h>
#include "defines.h"

//rekurzivni fce na kontrolu tokenu v 8mi smerech
//pokud se token na aktualni rovna tokenu, ktery ma fce sbirat (argument token),
//pripocte k promenne count. Pokud se jiz count rovna argumentu count_to_win,
//ve kterem se uchovava pocet tokenu potrebnych k vyhre, vrati true. Jinak
//se rekurzivne zavola v onom urcitem smeru (1..8), ktery se predava v argumentu direction
int check_rec_a(TGarray game_board, int x, int y, int direction, int* count, int token, int count_to_win)
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

//hleda ve vsech smerech, jestli nekde neexistuje vyherni kombinace tokenu
//kterou udava argument count_to_win
int check_win_a(TGarray game_board, int token, int count_to_win)
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

//posledni z kontrolovacich fci, ktery zavola check_rec_a ve vsech smerech
//od aktualniho tokenu, secte pocet tokenu v protilehlych smerech
//(count a count2) a zkontroluje, jestli se rovna poctu vyhernich tokenu (argument towin)
int check_act(TGarray game_board, int token, int i, int j, int towin)
{
    int count, count2;
    count = count2 = 0;
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

//v teto fci kontroluji, jestli bude v budoucnu volno na umisteni vsech peti
//tokenu. Kvuli tomu, aby byla tato AI jednodussi, zakomentovano
int testmode(TGarray array, int token, int pos)
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

//hlavni fce, realizujici samotny vyber vhodne pozice
TCoord ai1(TGarray game_board, int symbol)
{
  //v promenne dir uchovavam vhodne souradnice
  TCoord dir;
  //promenna array je kopie herniho pole, se kterou pracuji pri hledani pozice
  TGarray array;
  //zde inicializuji svuj a protivnikuv symbol
  int mysymbol, othersymbol;
  mysymbol=symbol;
  if (symbol==CROSS) othersymbol=CIRCLE;
  else othersymbol=CROSS;
  for (int j=0;j<MAXY;j++)
      for (int i=0;i<MAXX;i++)
		array[i][j]=game_board[i][j]; //zkopiruji herni pole do array
  for (int j=0;j<MAXY;j++) //zde postupne zkusim na vsechna mista doplnit svuj symbol,
      for (int i=0;i<MAXX;i++) //pokud by to byla vyherni kombinace, vratim tyto souradnice a vyhraji
      {
		if (array[i][j]==NONA) {
			array[i][j]=mysymbol;
			if (check_win_a(array,mysymbol,TOKENS_TO_WIN)==1) {dir.x=i; dir.y=j; return dir;}
			array[i][j]=NONA;
		}
	  }
  for (int j=0;j<MAXY;j++) //zde zkusim totez jako predtim, ale s protivnikovym znakem
      for (int i=0;i<MAXX;i++) //pokud by snad nekde mohl vyhrat, zamezim mu tim, ze tam dam vlastni token
	  {
		if (array[i][j]==NONA) {
			array[i][j]=othersymbol;
			if (check_win_a(array,othersymbol,TOKENS_TO_WIN)==1) {dir.x=i; dir.y=j; return dir;}
			array[i][j]=NONA;
		}
	  }
  for (int j=MAXY-1;j>=0;j--) //zde zkusim, zda by protivnik nemohl utvorit ctverici
      for (int i=MAXX-1;i>=0;i--)
	  {
		if (array[i][j]==NONA) {
			array[i][j]=othersymbol;
            if (check_act(array,othersymbol,i,j,TOKENS_TO_WIN)==1) if (testmode(array,othersymbol,TOKENS_TO_WIN-1)) {dir.x=i; dir.y=j; return dir;}
			array[i][j]=NONA;
		}
	  }
  for (int f=TOKENS_TO_WIN; f>2 ;f--) //zde opakuji predchozi doplnovani mych znaku,
	  { //ale predpokladam, ze je ke hre potreba od TOKENS_TO_WIN do tri tokenu
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
  for (int j=1;j<(MAXY-1);j++) //toto znamena, ze jsou umistene jenom dva tokeny,
      for (int i=1;i<(MAXX-1);i++) //takze aspon pripojim tenhle k jiz umistenemu
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
  dir.x = MAXX/2; //toto znamena, ze jsem zacinajici a mam prvni tah.
  dir.y = MAXY/2; //dam token doprostred herniho pole
  return dir;
}
