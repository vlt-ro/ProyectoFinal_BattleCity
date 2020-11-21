/*
 * Game.h
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#ifndef STATES_GAME_H_
#define STATES_GAME_H_

#include "state.h"
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using namespace std;

class Game: public State
{
public:
	Game();
	virtual ~Game();

	// Inherit methods
	void inputKey(string key);
	int task();
	void gameOver();
	void score();
	bool start();
	bool stop();

	map<string, SDL_Texture*> texturaGame;

private:
};

#endif /* STATES_GAME_H_ */
