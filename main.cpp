#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_gfxPrimitives_font.h>
//#include <SDL/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <ctime>
#include "defines.h"
#include "core.h"
#include "ai1.h"
#include "ai2.h"

using namespace std;

void init_screen( SDL_Surface* screen );

void draw_screen( SDL_Surface* screen, GARRAY game_board, int win=0);

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(MAXX*40, MAXY*40, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 600x600 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption("Gomoku GUI version", NULL);

//    if(TTF_Init() == -1)
//	{
//		printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
//		return false;
//	}
//
//	TTF_Font* g_font = TTF_OpenFont("DejaVuSansCondensed.ttf", 16);
//	if(!g_font)
//	{
//		printf("Unable to open font: %s\n", TTF_GetError());
//		return false;
//	}
//	SDL_Color text_col = {255, 255, 255, 0};
//	SDL_Rect text_rec = {20, 20, 0, 0};
//	SDL_Surface *text;

    GARRAY game_board;
    clear_board(game_board);
    bool gamer_play=true;
    bool play=true;
    bool notice_win=true;
    ai1 ai;
    int won=0;

    // program main loop
    bool done = false;
    while (!done)
    {//TODO: oznamovani vyhry
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            SDL_Delay(10);
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                // check for keypresses
                case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            //TODO:tohle
                            if ((play==true)&&(gamer_play==true)&&game_board[int((event.button.x)/40)][int((event.button.y)/40)]==NONA)
                             {game_board[int((event.button.x)/40)][int((event.button.y)/40)]=CROSS; gamer_play=false;}
                            break;
                    }
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        if (check_win(game_board, CROSS)) {
                if(notice_win)
                    {
                        won=1;
                        notice_win=false;
                        cout << "Player wins the game.\n";
                        stringColor(screen,10,10,"Player wins the game.",RED);
                        SDL_Flip(screen);
//                        text = TTF_RenderUNICODE_Blended(g_font,"Player has won the game.",BLACK);
//                        if(text != NULL)
//                        {
//                            SDL_BlitSurface(text, NULL, screen, &text_rec);
//                        }
                    }
                play=false;
        }
        if (check_win(game_board, CIRCLE)) {
                if(notice_win)
                {
                    won=2;
                    notice_win=false;
                    cout << "AI wins the game.\n";
                    stringColor(screen,10,10,"AI wins the game.",RED);
                    SDL_Flip(screen);
//                    text = TTF_RenderUNICODE_Blended(g_font,"AI has won the game.",BLACK);
//                    if(text != NULL)
//                    {
//                        SDL_BlitSurface(text, NULL, screen, &text_rec);
//                    }
                }
                play=false;
        }

        init_screen(screen);
        draw_screen(screen,game_board, won);

        SDL_Flip(screen);

        if((gamer_play==false)&&(play==true)) {
            DIRECTIONS dir;
//            sleep(1);
            GARRAY game_board_safe;
            copy_array(game_board,game_board_safe);
            dir = ai.play(game_board_safe);
            if (game_board[dir.x][dir.y]!=NONA)
                {
                    stringColor(screen,10,10,"AI is a cheater and had lost the game!",RED);
                    SDL_Flip(screen);
                    cout << "AI is a cheater and had lost the game!\n";
                    play=false;
                }
            game_board[dir.x][dir.y]=CIRCLE;

            gamer_play=true;

            init_screen(screen);
            draw_screen(screen,game_board, won);
            // finally, update the screen :)
            SDL_Flip(screen);
        }

        if (check_win(game_board, CROSS)) {
                if(notice_win) {notice_win=false; stringColor(screen,10,10,"Player wins the game.",RED); SDL_Flip(screen);
                    won=1; cout << "Player wins the game.\n";}
                play=false;
        }
        if (check_win(game_board, CIRCLE)) {
                if(notice_win) {notice_win=false; stringColor(screen,10,10,"AI wins the game.",RED); SDL_Flip(screen);
                    won=2; cout << "AI wins the game.\n";}
                play=false;
        }
        // DRAWING ENDS HERE

    } // end main loop
//    SDL_FreeSurface(text);
//
//    if (g_font!=NULL)
//    {
//        TTF_CloseFont(g_font);
//		g_font = NULL;
//    }
//    TTF_Quit();

    // all is well ;)

    printf("Exited cleanly\n");
    return 0;
}

void init_screen( SDL_Surface* screen)
{
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));
    for (int i=0;i<MAXX*40;i++)
    {
        if (((i%40)==0)&&(i!=0)) vlineColor(screen, i, 5, MAXY*40-5, BLACK_PAPER);
    }
    for (int i=0;i<MAXY*40;i++)
    {
        if (((i%40)==0)&&(i!=0)) hlineColor(screen, 5, MAXX*40-5, i, BLACK_PAPER);
    }
}

void draw_screen(SDL_Surface* screen, GARRAY game_board, int win)
{
    for (int i=0;i<MAXX;i++)
        for (int j=0;j<MAXY;j++)
        {
            if (game_board[i][j]==CIRCLE) circleColor(screen,(i*40)+20,(j*40)+20,15,RED);
            else if (game_board[i][j]==CROSS)
            {
                lineColor(screen,(i*40)+3,(j*40)+3,((i+1)*40)-3,((j+1)*40)-3,BLACK);
                lineColor(screen,(i*40)+3,((j+1)*40)-3,((i+1)*40)-3,(j*40)+3,BLACK);
            }
        }
    if (win==1) stringColor(screen,10,10,"Player wins the game.",RED);
    else if (win==2) stringColor(screen,10,10,"AI wins the game.",RED);
}
