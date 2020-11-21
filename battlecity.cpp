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
#include "config.h"
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
    //map();
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
        int state = 0;

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
                	currState->inputKey(SDL_GetKeyName(e.key.keysym.sym));
                }
            }

            //TODO: read returned value
            state = currState->task();

            switch(state)
            {
            	case 1:
            		delete currState;
                    currState = new Game;
                    currState->start();


                    break;
            	case 2:
            		printf("Esta modalidad no está disponible");
            		quit = true;
            		break;
            	case 3:
            		quit = true;
            		break;
            }


        }

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
		window = SDL_CreateWindow( "BATTLE_CITY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

