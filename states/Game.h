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
	 * Eventos que serán retornados por método task.
	 */
	enum
	{
		eCONTINUE = 0,  //< Estado: Continua el juego
		eVICTORY = 0x05,//< Estado: Gana el juego
		eDEFEAT,        //< Estado: Pierde el juego
	};

	Game();
	virtual ~Game();

	void inputKey(string key);
	int task();
	bool start();
	bool stop();

private:
	map<string, SDL_Texture*> texturaGame;
	vector<GObject*> objects;
	Ally *ally;
	int status;
	vector <Bullet*> bullets;
	SDL_Keycode currKey;
	vector<vector<int>> enemy_counter;
	int n_lifes;
	unsigned int enemyTicks;

	void moveAlly();
	void moveBullets();
	void moveEnemies();

	void destroyFlag();
	void destroyEnemy(int ind);
	void gameOver();
	void score();
	void drawObject(GObject &obj);
	void destroyObject(int ind);
	void createAlly();
	void destroyAlly();
};

#endif /* STATES_GAME_H_ */
