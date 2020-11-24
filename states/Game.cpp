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
	//mover enemigoSDL_Rect rect
	//disparar enemigo

	// aliados

	//int direction;

	switch(currKey)
	{
	case SDLK_UP:
		direction = DGObject::eUp;
		direction_temp = direction;
		break;
	case SDLK_DOWN:
		direction = DGObject::eDown;
		direction_temp = direction;
		break;
	case SDLK_LEFT:
		direction = DGObject::eLeft;
		direction_temp = direction;
		break;
	case SDLK_RIGHT:
		direction = DGObject::eRight;
		direction_temp = direction;
		break;
	case SDLK_SPACE:
		bullet_ = true;
		direction_bullet = direction_temp;
		/*if (!bullet_)
		{
			bullet_ally.setPosition(ally.getPosition().x+8,ally.getPosition().y+8);
			bullet_ = true;
			direction_bullet = direction_temp;
		}*/
		break;

	default:
		direction = -1;
	}
	currKey = SDLK_UNKNOWN; //clear key

	SDL_Rect obstacle={0,0,0,0};
	if (bullet_)
	{
		bullet_ally.push_back(Bullet(ally.getPosition().x+9,ally.getPosition().y+9,direction_bullet));
		bullet_ = false;
	}

	for (int i=0; i<bullet_ally.size();i++)
	{
		Render::drawRect(bullet_ally[i].getDimension(),Render::black,true);
		obstacle = bullet_ally[i].move(Config::UN,objects );
		Render::drawObject(bullet_ally[i].getTexture(), bullet_ally[i].getPosition().x, bullet_ally[i].getPosition().y);

		if (obstacle.w==-1 )
		{
			Render::drawRect(bullet_ally[i].getDimension(),Render::black,true);
			bullet_ally.erase(bullet_ally.begin() + i);
		}
		else if (obstacle.w>0 and obstacle.h>0 )
		{
			Render::drawRect(obstacle,Render::black,true);
			Render::drawRect(bullet_ally[i].getDimension(),Render::black,true);
			bullet_ally.erase(bullet_ally.begin() + i);
		}
		else if (bullet_ally[i].getDimension().x==0 )
		{
			bullet_ally.erase(bullet_ally.begin() + i);
		}
	}

	Render::drawRect(ally.getDimension(),Render::black,true);
	ally.move(direction, Config::UN, objects );
	Render::drawObject(ally.getTexture(), ally.getPosition().x, ally.getPosition().y);
	Render::presentRender();
	SDL_Delay(100);

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
					objects.insert(pair <string, GObject> ("bricks", Brick(xPos,yPos)));
					obstacles.push_back(Brick(xPos,yPos));
					Render::drawObject(obstacles.back().getTexture(), xPos, yPos);
					break;
				case 'c':
					objects.insert(pair <string, GObject> ("concrete", Concrete(xPos,yPos)));
					obstacles.push_back(Concrete(xPos,yPos));
					Render::drawObject(obstacles.back().getTexture(), xPos, yPos);
					break;
				case 'f':
					objects.insert(pair <string, GObject> ("flag", Flag(xPos,yPos)));
					flag.setPosition(xPos, yPos);
					Render::drawObject(flag.getTexture(), xPos, yPos);
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
