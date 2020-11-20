#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <SDL2/SDL_image.h>
#include "battlecity.h" 
#include  "graphics.h"

#include "states/MainMenu.h"
#include "states/Game.h"
#include "Render.h"

using namespace graphics;

using namespace std;

BattleCity::BattleCity():
		currState(nullptr),
		window(nullptr)
{

}

BattleCity::~BattleCity()
{
	if(currState)
		delete currState;

	SDL_DestroyWindow(window);
}

void BattleCity::gameRules() {}

void BattleCity::playLevel1()
{
    map();
}

void BattleCity::mainMenu()
{

    //Main loop flag
    bool quit = false;

    SDL_Color red= {0xFF, 0x33, 0x33, SDL_ALPHA_OPAQUE}; //Red
    SDL_Color white= {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE}; //White
    SDL_Color black = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE}; //Black

    int x= (SCREEN_WIDTH-404)/2;;
    SDL_Rect rect1;

    rect1.x = 145;
    rect1.y = 142;  
    rect1.w = 29;
    rect1.h = 29;
    SDL_RenderCopy(gRenderer, gTextures[3], NULL, &rect1);

    RenderText("prstartk.ttf", 68, "TANKS",white, 404,  74,  48, x);
    RenderText("tank_font.ttf", 58, "TANKS",red, 404,  74,  48, x );
    RenderText("prstartk.ttf", 58, "1 Player",white, 108,  15,  150,181 );
    RenderText("prstartk.ttf", 58, "2 Players",white, 124,  15,  188,181 );
    RenderText("prstartk.ttf", 58, "Exit",white, 52,  15,  218,181 );

    SDL_RenderPresent( gRenderer );

    //Event handler
    SDL_Event e;
    int counter = 0;

    //While application is running
    while( !quit )
    {
    	//Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            else if( e.type == SDL_KEYDOWN )
            {
            	currState->inputKey(e.key.keysym.sym);
//                switch( e.key.keysym.sym )
//                {
//                    case SDLK_DOWN:
//                        counter++;
//                        break;
//                    case SDLK_UP:
//                        counter--;
//                        break;
//                    case SDLK_RETURN:
//                        if (counter%3==2) quit=true;
//                        else if (counter%3==1)
//                        {
//                            quit =true    ;
//                            printf("El juego aun no sirve para 2 jugadores\n");
//                        }
//                        else if (counter%3==0)
//                        {
//                            //RenderRectangle(rect1.x, rect1.y, rect1.w, rect1.h, black, true);
//                            //SDL_RenderPresent( gRenderer );
//
//                            playLevel1();
//                        }
//                        break;
//                }
            }
            RenderRectangle(rect1.x, rect1.y, rect1.w, rect1.h, black, true);

            if (counter%3==2) rect1.y = 211;
            else if (counter%3==0)rect1.y = 142;

            else if (counter%3==1) rect1.y = 179;
            
            SDL_RenderCopy(gRenderer, gTextures[3], NULL, &rect1);
            SDL_RenderPresent( gRenderer );

        }
    }
    
    closeGraphics();
} 

void BattleCity::start()
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
    	currState = new MainMenu;

    	currState->start();

        //Event handler
        SDL_Event e;
        int counter = 0;

        //Main loop flag
        bool quit = false;
        //While application is running
        while( !quit )
        {
        	//Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                else if( e.type == SDL_KEYDOWN )
                {
                	currState->inputKey(e.key.keysym.sym);
                }
            }

            //TODO: read returned value
            currState->task();

            //delete currState;
            //currState = new GameSate;
            //currState->start()
        }

//        //Load media
//        if( !loadMedia() )
//        {
//            printf( "Failed to load media!\n" );
//        }
//        else
//        {
//            mainMenu();
//        }
    }

}

void BattleCity::closeGraphics()
{
    //Free resources and close SDL
    close();
}

bool BattleCity::init()
{

	//Initialization flag
	bool success = false;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "BATTLE_CITY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		else
		{
			try
			{
				Render::init(window);
				success = true;
			}
			catch(std::string &e)
			{
				printf("%s\n",e.c_str());
			}
		}
	}

	return success;
}

