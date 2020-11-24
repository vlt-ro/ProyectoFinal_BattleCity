/*
 * Enemy.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: santiago
 */

#include "Enemy.h"
#include "../config.h"

Enemy::Enemy(int x, int y):
	Tank(Config::txEnemy[0].h, Config::txEnemy[0].w, x, y)
{
	/* load textures */
	for(int i=0; i<4; i++)
		textures[i] = Config::txEnemy[i];
	orientation = eUp;
	setTexture(&textures[eUp]);
}

Enemy::~Enemy()
{
}

