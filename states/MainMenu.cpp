/*
 * MainMenu.cpp
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#include "MainMenu.h"
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

MainMenu::MainMenu()
{
	counter = 0;
}

MainMenu::~MainMenu()
{

}

void MainMenu::inputKey(string key)
{
	currKey = key;

	if (currKey=="Down") {counter++;}
	else if (currKey=="Up") {counter--;}
}

int MainMenu::task()
{
	if (currKey=="Down" or currKey=="Up")
	{
		Render::drawRect(145, yPos, 29, 29, Render::black, true);

		if (counter%3==2) yPos = 211;
		else if (counter%3==1) yPos = 179;
		else if (counter%3==0) yPos = 142;

		Render::drawObject(145, yPos, 29, 29, texturaMainMenu["ally"]);
		Render::presentRender();

		currKey="";
		return 0;
	}
	else if (currKey=="Return")
	{
		currKey="";
		if (counter%3==0)
		{
			return 1;
		}
		else if (counter%3==1)
		{
			return 2;
		}
		else if (counter%3==2)
		{
			return 3;
		}
	}
	else
		currKey="";
		return 4;
}

bool MainMenu::start()
{
	ifstream file1(Config::textureMainMenu.c_str());
    ifstream file2(Config::textureMainMenu_names.c_str());

    string str;
    vector<string> texturas;
    vector<string> texturas_names;

    while (getline(file1,str)){ texturas.push_back(str);}
    while (getline(file2,str)){ texturas_names.push_back(str);}

    for (int i = 0; i < texturas.size(); ++i)
    {
        texturaMainMenu.insert(pair<string, SDL_Texture*>(texturas_names[i], Render::loadTexture( texturas[i])));
    }


    Render::drawText((Config::SCREEN_WIDTH-404)/2, 48, 404, 74, Render::white, Config::font_prstartk, 68, "TANKS");
    Render::drawText((Config::SCREEN_WIDTH-404)/2, 48, 404, 74, Render::red, Config::font_tank, 58, "TANKS");
    Render::drawText(181, 150, 108, 15, Render::white, Config::font_prstartk, 58, "1 Player");
    Render::drawText(181, 188, 124, 15, Render::white, Config::font_prstartk, 58, "2 Players");
    Render::drawText(181, 218, 52, 15, Render::white, Config::font_prstartk, 58, "Exit");
    Render::drawObject(145, yPos, 29, 29, texturaMainMenu["ally"]);

    Render::presentRender();

	return false;
}



bool MainMenu::stop()
{
	//texturas
	//cargar mapa
	return false;
}

