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

	/**
	 * Events returned by the "task" method
	 */
	enum
	{
		eCONTINUE = 0,
		eVICTORY = 0x05,///< Mode "one player" was selected
		eDEFEAT,      ///< Mode "Two player" was selected
	};

	Game();
	virtual ~Game();

	// Inherit methods
	void inputKey(string key);
	int task();
	void destroyEnemy();
	void deathCounter();
	void gameOver();
	void score();
	bool start();
	bool stop();

private:
	map<string, SDL_Texture*> texturaGame;
	vector<GObject*> obstacles;
	Ally *ally;
	int status = eCONTINUE;
	vector <Bullet*> bullets;
	SDL_Keycode currKey;
	bool bullet_ = false;
	int direction = -1;
	int direction_bullet = -1;
	int direction_temp = DGObject::eUp;

	int n_enemy = 0;
	vector<vector<int>> enemy_counter;
	int n_lifes = 10;
	int puntaje = 0;
	bool death = false;
	bool isFlagDestroyed;

	void drawObject(GObject &obj);
	void destroyObject(int ind);
	void createAlly();
	void destroyAlly();
};

#endif /* STATES_GAME_H_ */
