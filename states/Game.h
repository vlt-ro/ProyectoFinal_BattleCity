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
#include <vector>
#include <string>
#include <iterator>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../g_objects/g_object.h"
#include "../g_objects/Flag.h"
#include "../g_objects/ally.h"
#include "../g_objects/Bullet.h"

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

private:
	map<string, SDL_Texture*> texturaGame;
	vector<GObject> obstacles;
	multimap <string, GObject> objects;
	multimap <string, GObject> :: iterator itr;
	Flag flag;
	Ally ally;

	vector <Bullet> bullet_ally;
	SDL_Keycode currKey;
	bool bullet_ = false;
	int direction = -1;
	int direction_bullet = -1;
	int direction_temp = DGObject::eUp;
};

#endif /* STATES_GAME_H_ */
