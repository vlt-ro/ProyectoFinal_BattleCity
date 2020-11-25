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
#include <iterator>
#include "../g_objects/Brick.h"
#include "../g_objects/Concrete.h"
#include "../g_objects/Bullet.h"

using std::string;
using namespace std;

Game::Game():
		flag(0,0),
		ally(0,0)
{
	currKey = SDLK_UNKNOWN;
}

Game::~Game()
{
	stop();
}

void Game::inputKey(string key)
{
	if(key == "Up")
		currKey = SDLK_UP;
	else if(key == "Down")
		currKey = SDLK_DOWN;
	else if(key == "Right")
		currKey = SDLK_RIGHT;
	else if(key == "Left")
		currKey = SDLK_LEFT;
	else if(key == "Space")
		currKey = SDLK_SPACE;
}

int Game::task()
{
	Bullet *b;
	switch(currKey)
	{
	case SDLK_UP:
		Render::drawRect(ally.getDimension(),Render::black,true);
		ally.move(Config::UN/2, obstacles, DGObject::eUp);
		break;
	case SDLK_DOWN:
		Render::drawRect(ally.getDimension(),Render::black,true);
		ally.move(Config::UN/2, obstacles, DGObject::eDown);
		break;
	case SDLK_LEFT:
		Render::drawRect(ally.getDimension(),Render::black,true);
		ally.move(Config::UN/2, obstacles, DGObject::eLeft);
		break;
	case SDLK_RIGHT:
		Render::drawRect(ally.getDimension(),Render::black,true);
		ally.move(Config::UN/2, obstacles, DGObject::eRight);
		break;
	case SDLK_SPACE:
		b = ally.shoot();
		if(b)
			bullets.push_back(b);
		break;

	default:
		direction = -1;
	}
	currKey = SDLK_UNKNOWN; //clear key

	SDL_Rect obstacle={0,0,0,0};

	for(auto bIt = bullets.begin(); bIt < bullets.end(); bIt++)
	{
		auto &b = (*bIt);

		SDL_Point oldPos = b->getPosition();
		Render::drawRect(b->getDimension(), Render::black, true);
		int ind = b->move(Config::UN,obstacles);
		if( ind >= 0)
		{
			if(obstacles[ind].getID() != Config::CONCRETE)
			{
				Render::drawRect(obstacles[ind].getDimension(),Render::black,true);
				obstacles.erase(obstacles.begin()+ind);
			}
		}

		if(oldPos.x == b->getPosition().x && oldPos.y == b->getPosition().y)
		{
			delete b;
			bullets.erase(bIt);
			continue;
		}
		drawObject(*b);
	}

	Render::drawObject(ally.getTexture(), ally.getPosition().x, ally.getPosition().y);
	Render::presentRender();
	SDL_Delay(70);

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
	ifstream file1(Config::textureGame);
    ifstream file2(Config::textureGame_names);

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

    ifstream file(Config::mapLevel1);

    vector<string> mapa;

    while (getline(file,str)){ mapa.push_back(str);}

    obstacles.clear();
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
					obstacles.push_back(Brick(xPos,yPos));
					Render::drawObject(obstacles.back().getTexture(), xPos, yPos);
					break;
				case 'c':
					obstacles.push_back(Concrete(xPos,yPos));
					Render::drawObject(obstacles.back().getTexture(), xPos, yPos);
					break;
				case 'f':
					obstacles.push_back(Flag(xPos,yPos));
					Render::drawObject(obstacles.back().getTexture(), xPos, yPos);
//					flag.setPosition(xPos, yPos);
//					Render::drawObject(flag.getTexture(), xPos, yPos);
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
			}
    	}
    }

	return true;
}

bool Game::stop()
{
	//limpiar (destruir) _todo
	return false;
}


void Game::drawObject(GObject &obj)
{
	Render::drawObject(obj.getTexture(), obj.getPosition().x, obj.getPosition().y);
}

