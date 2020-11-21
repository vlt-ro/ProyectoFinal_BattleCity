/*
 * Game.cpp
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#include "Game.h"
#include "../Render.h"
#include "../config.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <stdio.h>

using std::string;
using namespace std;

Game::Game()
{

}

Game::~Game()
{

}

void Game::inputKey(string key)
{
	//switch(key)
	// ... accion = algo
	//

}

int Game::task()
{
	//mover enemigo
	//disparar enemigo

	// aliados
	//switch(accion)
	// ...
	//

	//actualizar pantalla

	return 0;
}

void Game::gameOver()
{
	for(int i = 0; i<8; i++)
	{
		Render::drawRect(0, (Config::SCREEN_HEIGHT-26)-(i-1)*26, Config::SCREEN_WIDTH, 26, Render::black, true);
		Render::drawText((Config::SCREEN_WIDTH-196-48)/2,(Config::SCREEN_HEIGHT-26)-i*26, 256, 26, Render::red, Config::font_prstartk, 68, "GAME OVER");

		Render::drawRect(0, (26)+(i-1)*26, Config::SCREEN_WIDTH, 26, Render::black, true);
		Render::drawText((Config::SCREEN_WIDTH-196-48)/2,(26)+i*26, 256, 26, Render::red, Config::font_prstartk, 68, "GAME OVER");

		if (i==7)
		{
			Render::drawRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Render::black, true);
			Render::drawText((Config::SCREEN_WIDTH-196-48)/2,8*26, 256, 26, Render::red, Config::font_prstartk, 68, "GAME OVER");
		}

		Render::presentRender();
		SDL_Delay(250);
	}

	score();
}
void Game::score()
{
	Render::drawRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Render::black, true);
	Render::presentRender();
	SDL_Delay(250);

    Render::drawText((Config::SCREEN_WIDTH-196)/2,10, 196, 28, Render::white, Config::font_prstartk, 68, "STAGE 1");
    Render::drawText((Config::SCREEN_WIDTH-240)/2,53, 240, 12, Render::white, Config::font_prstartk, 58, "PLAYER				SCORE");
    Render::drawRect((Config::SCREEN_WIDTH-300)/2, 75, 300, 2, Render::white, true);

    Render::drawObject(107,93, 29, 29, texturaGame["ally"]);
    Render::drawText(143, 98,27, 14, Render::white, Config::font_prstartk, 68, "x5");

    Render::presentRender();
	SDL_Delay(250);

	int puntaje = 200;

	for (int i=0; i<=puntaje;i++)
	{
	    Render::drawRect(266, 95, 40, 14, Render::black, true);
	    Render::drawText(266, 95, 40, 14, Render::white, Config::font_prstartk, 68, std::to_string(i));
	    Render::presentRender();
	    SDL_Delay(20);
	}


}

bool Game::start()
{
	ifstream file1(Config::textureGame.c_str());
    ifstream file2(Config::textureGame_names.c_str());

    string str;
    vector<string> texturas;
    vector<string> texturas_names;

    while (getline(file1,str)){ texturas.push_back(str);}
    while (getline(file2,str)){ texturas_names.push_back(str);}

    for (int i = 0; i < texturas.size(); ++i)
    {
        texturaGame.insert(pair<string, SDL_Texture*>(texturas_names[i], Render::loadTexture( texturas[i])));
    }

    Render::drawRect(0,0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Render::gray, true);
    Render::drawText((Config::SCREEN_WIDTH-196)/2,(Config::SCREEN_HEIGHT-28)/2, 196, 28, Render::white, Config::font_prstartk, 68, "STAGE 1");

    Render::presentRender();

    SDL_Delay(1500);

    Render::drawRect(0, 0, Config::SCREEN_WIDTH-48, Config::SCREEN_HEIGHT, Render::black, true);
    Render::drawRect(Config::SCREEN_WIDTH-48, 0, 48, Config::SCREEN_HEIGHT, Render::gray, true);

    ifstream file(Config::mapLevel1.c_str());

    vector<string> mapa;

    while (getline(file,str)){ mapa.push_back(str);}

    int xPos,yPos;
    for (int i = 0; i < mapa.size(); ++i)
    {
    	for (int j = 0; j < mapa[0].size(); ++j)
    	{
    		xPos = j*Config::UN;
    		yPos = i*Config::UN;

    		switch(mapa[i][j])
    		{
				case 'b':
					Render::drawObject(xPos, yPos, Config::UN, Config::UN, texturaGame["bricks"]);
					break;
				case 'c':
					Render::drawObject(xPos, yPos, Config::UN, Config::UN, texturaGame["concrete"]);
					break;
				case 'f':
					Render::drawObject(xPos, yPos, 2*Config::UN, 2*Config::UN, texturaGame["flag"]);
					break;

				case 'e':
					Render::drawObject(xPos-6, yPos-6, Config::UN-2, Config::UN-2, texturaGame["enemy_g"]);
					break;
				case 'a':
					Render::drawObject(xPos-10, yPos-10, Config::UN, Config::UN, texturaGame["ally"]);
					Render::drawText(xPos+8, yPos-8, 15, 15, Render::black, Config::font_prstartk, 32, "10");
					break;
				case 'g':
					Render::drawObject(xPos-6, yPos-6, 31, 26, texturaGame["flag_g"]);
					Render::drawText(xPos+4, yPos+Config::UN , 15, 15, Render::black, Config::font_prstartk, 32, "1");

					break;
				//case '.':
				//case '  ':
					//break;
				//default:
					//printf("Textura desconocida\n");
					//cout<<mapa[i][j]<<endl;
			}
    	}
    }

    Render::presentRender();

    SDL_Delay(1500);

    gameOver();

	return false;
}

bool Game::stop()
{
	//limpiar (destruir) _todo
	return false;
}

