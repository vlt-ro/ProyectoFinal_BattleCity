/*
 * MainMenu.h
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#ifndef STATES_MAINMENU_H_
#define STATES_MAINMENU_H_

#include "state.h"
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using namespace std;

class MainMenu: public State
{
public:
	MainMenu();
	virtual ~MainMenu();

	// Inherit methods
	void inputKey(string key);
	int task();
	bool start();
	bool stop();

    map<string, SDL_Texture*> texturaMainMenu;
private:
    int yPos = 142;
    int counter;
    string currKey="";
};

#endif /* STATES_MAINMENU_H_ */
