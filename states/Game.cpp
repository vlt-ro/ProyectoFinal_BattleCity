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
#include <algorithm>
#include <utility>
#include <stdio.h>
#include <iterator>
#include "../g_objects/Brick.h"
#include "../g_objects/Concrete.h"
#include "../g_objects/Enemy.h"

using std::string;
using namespace std;

namespace
{
//	#define NPOS 3
	SDL_Point EnemyPos[] =  {
								{0,32},
								{20*Config::UN,64},
								{12*Config::UN,32},
								{24*Config::UN,0}
							};
	const std::size_t NPOS = sizeof(EnemyPos)/sizeof(SDL_Point);
	int curEnemyPos = NPOS-1;
}

Game::Game()
{
	ally = nullptr;
	currKey = SDLK_UNKNOWN;
	status = eCONTINUE;
	n_lifes = 10;
	enemyTicks = SDL_GetTicks();
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
	moveAlly();
	moveEnemies();
	moveBullets();

	if(status == eCONTINUE)
	{
		Render::presentRender();
		SDL_Delay(70);
	}
	return status;
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

    for (unsigned i = 0; i < texturas.size(); ++i)
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

    objects.clear();
    int xPos,yPos;
    for (unsigned i = 0; i < mapa.size(); ++i)
    {
    	for (unsigned j = 0; j < mapa[0].size(); ++j)
    	{
    		xPos = j*Config::UN;
    		yPos = i*Config::UN;
    		switch(mapa[i][j])
    		{
				case 'b':
					objects.push_back(new Brick(xPos,yPos));
					Render::drawObject(objects.back()->getTexture(), xPos, yPos);
					break;
				case 'c':
					objects.push_back(new Concrete(xPos,yPos));
					Render::drawObject(objects.back()->getTexture(), xPos, yPos);
					break;
				case 'f':
					objects.push_back(new Flag(xPos,yPos));
					Render::drawObject(objects.back()->getTexture(), xPos, yPos);
					break;
				case 'e':
					Render::drawObject(xPos-6, yPos-6, Config::UN-2, Config::UN-2, texturaGame["enemy_g"]);
					enemy_counter.push_back({xPos-6, yPos-6});
					break;
				case 'a':
					Render::drawObject(xPos-10, yPos-10, Config::UN, Config::UN, texturaGame["ally"]);
					Render::drawText(xPos+8, yPos-8, 15, 15, Render::black, Config::font_prstartk, 32, to_string(n_lifes));
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
	delete ally;
	for(auto it=objects.begin(); it<objects.end(); it++)
		delete (*it); //Free memory
	for(auto it=bullets.begin(); it<bullets.end(); it++)
		delete (*it); //Free memory
	//TODO: free texturaGame
	return false;
}

void Game::moveAlly()
{
	if(ally)
	{
		Bullet *b;
		switch(currKey)
		{
		case SDLK_UP:
			Render::drawRect(ally->getDimension(),Render::black,true);
			ally->move(Config::UN/2, objects, DGObject::eUp);
			break;
		case SDLK_DOWN:
			Render::drawRect(ally->getDimension(),Render::black,true);
			ally->move(Config::UN/2, objects, DGObject::eDown);
			break;
		case SDLK_LEFT:
			Render::drawRect(ally->getDimension(),Render::black,true);
			ally->move(Config::UN/2, objects, DGObject::eLeft);
			break;
		case SDLK_RIGHT:
			Render::drawRect(ally->getDimension(),Render::black,true);
			ally->move(Config::UN/2, objects, DGObject::eRight);
			break;
		case SDLK_SPACE:
			b = ally->shoot();
			if(b)
				bullets.push_back(b);
			break;
		}
		currKey = SDLK_UNKNOWN; //clear key
		drawObject(*ally);
	}
	else
		createAlly();
}

void Game::moveBullets()
{
	for(auto bIt = bullets.begin(); bIt < bullets.end(); bIt++)
	{
		auto &b = (*bIt);

		SDL_Point oldPos = b->getPosition();
		Render::drawRect(b->getDimension(), Render::black, true);
		int ind = b->move(Config::UN,objects);
		if( ind >= 0)
		{
			switch(objects[ind]->getID())
			{
			case Config::CONCRETE:
				break;
			case Config::ALLY:
				destroyAlly();
				break;
			case Config::ENEMY:
				destroyEnemy(ind);
				break;
			case Config::FLAG:
				destroyFlag();
				break;
			default:
				destroyObject(ind);
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
}

void Game::moveEnemies()
{
	unsigned n_enemytemp = 0;
	for(auto obj : objects)
	{
		if(obj->getID() == Config::ENEMY)
		{
			Render::drawRect(obj->getDimension(),Render::black,true);
			Enemy *pObj = dynamic_cast<Enemy*>(obj);
			if(pObj)
			{
				pObj->move(Config::UN/4,objects);
				Bullet *b = pObj->shoot();
				if(b)
					bullets.push_back(b);
			}
			drawObject(*obj);
			n_enemytemp += 1;
		}
	}

	unsigned int cticks = SDL_GetTicks();
	if (n_enemytemp < std::min(NPOS, enemy_counter.size()) &&
		cticks > enemyTicks)
	{
		enemyTicks = cticks + rand()%3000 + 1000;
		curEnemyPos = (curEnemyPos + 1)%NPOS;
		objects.push_back(new Enemy(EnemyPos[curEnemyPos].x, EnemyPos[curEnemyPos].y));
		drawObject(*objects.back());
	}
}

void Game::destroyFlag()
{
	for(auto it=objects.begin(); it<objects.end(); it++)
	{
		if((*it)->getID() == Config::FLAG)
		{
			Render::drawRect((*it)->getDimension(), Render::black, true);
			delete (*it); //free memory
			objects.erase(it); //Remove the ally from the obstacles vector
			Render::drawObject(&Config::txDestroyedFlag, 192, 384);
			Render::presentRender();
			SDL_Delay(2000);
			gameOver();
			status = eDEFEAT;
			return;
		}
	}
}

void Game::destroyEnemy(int ind)
{
	if(enemy_counter.size() <= 1)
	{
		score();
		status = eVICTORY;
	}
	else
	{
		Render::drawRect(enemy_counter.back()[0],enemy_counter.back()[1], 14, 14, Render::gray, true);
		enemy_counter.pop_back();

		Render::drawRect(objects[ind]->getDimension(), Render::black, true);
		delete objects[ind];
		objects.erase(objects.begin()+ind);
		status = eCONTINUE;
	}
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
	int puntaje = n_lifes*50 + (13-enemy_counter.size())*20;

	Render::drawRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Render::black, true);
	Render::presentRender();
	SDL_Delay(250);

    Render::drawText((Config::SCREEN_WIDTH-196)/2,10, 196, 28, Render::white, Config::font_prstartk, 68, "STAGE 1");
    Render::drawText((Config::SCREEN_WIDTH-240)/2,53, 240, 12, Render::white, Config::font_prstartk, 58, "PLAYER				SCORE");
    Render::drawRect((Config::SCREEN_WIDTH-300)/2, 75, 300, 2, Render::white, true);

    Render::drawObject(107,93, 29, 29, texturaGame["ally"]);
    Render::drawText(143, 98,27, 14, Render::white, Config::font_prstartk, 68, "x"+to_string(n_lifes));

    Render::presentRender();
	SDL_Delay(250);

	for (int i=0; i<=puntaje;i+=10)
	{
	    Render::drawRect(266, 95, 40, 14, Render::black, true);
	    Render::drawText(266, 95, 40, 14, Render::white, Config::font_prstartk, 68, std::to_string(i));
	    Render::presentRender();
	    SDL_Delay(20);
	}
	SDL_Delay(2000);
	Render::drawRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Render::black, true);

}

void Game::drawObject(GObject &obj)
{
	Render::drawObject(obj.getTexture(), obj.getPosition().x, obj.getPosition().y);
}

void Game::destroyObject(int ind)
{
	Render::drawRect(objects[ind]->getDimension(),Render::black,true);
	delete objects[ind];
	objects.erase(objects.begin()+ind);
}

void Game::createAlly()
{
	if(n_lifes > 0)
	{
		ally = new Ally(32*4, Config::SCREEN_HEIGHT-32);
		if(ally)
		{
			objects.push_back(ally);
			drawObject(*ally);
		}
	}
}

void Game::destroyAlly()
{
	if(--n_lifes > 0 && ally)
	{
		for(auto it=objects.begin(); it<objects.end(); it++)
		{
			if((*it)->getID() == Config::ALLY)
			{
				Render::drawRect(27*Config::UN+8, 12*Config::UN-8, 16, 16, Render::gray, true);
				Render::drawText(27*Config::UN+8, 12*Config::UN-8, 15, 15, Render::black, Config::font_prstartk, 32, to_string(n_lifes));
				Render::drawRect(ally->getDimension(), Render::black, true);
				objects.erase(it); //Remove the ally from the obstacles vector
				delete ally; //free memory
				ally = nullptr;
				createAlly();
				return;
			}
		}
	}
	else
	{
			gameOver();
			status = eDEFEAT;
	}
}

