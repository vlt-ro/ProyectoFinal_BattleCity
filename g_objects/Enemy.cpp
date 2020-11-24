/*
 * Enemy.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: santiago
 */

#include "Enemy.h"
#include "../config.h"

namespace
{
	SDL_Rect txEnemy[4] = { {8*Config::UN,  0, 32, 32}, //UP
							{12*Config::UN, 0, 32, 32}, //Down
							{14*Config::UN, 0, 32, 32}, //Left
							{10*Config::UN, 0, 32, 32}};//Right
}

Enemy::Enemy(int x, int y):
	DGObject(txEnemy[0].h, txEnemy[0].w, x, y)
{
	/* load textures */
	for(int i=0; i<4; i++)
		textures[i] = txEnemy[i];
	orientation = eUp;
	setTexture(&textures[eUp]);
}

Enemy::~Enemy()
{
}

