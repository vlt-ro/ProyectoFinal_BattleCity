/*
 * Enemy.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: santiago
 */

#include "Enemy.h"
#include "../config.h"
#include <cstdlib>
#include <ctime>

bool Enemy::isSeedInitilized = false;

Enemy::Enemy(int x, int y):
	Tank(Config::txEnemy[0].h, Config::txEnemy[0].w, x, y)
{
	if(!isSeedInitilized)
	{
		srand(time(nullptr));
		isSeedInitilized = true;
	}

	/* load textures */
	for(int i=0; i<4; i++)
		textures[i] = Config::txEnemy[i];
	orientation = eUp;
	setTexture(&textures[eUp]);
	setID(Config::ENEMY);

	/* Set initial times */
	ticks = SDL_GetTicks();
	ticksShoot = ticks;
}

int Enemy::move(int step, vector<GObject*> &obj, int direction)
{
	unsigned int cticks = SDL_GetTicks();
	if(cticks > ticks + 1000)
	{
		ticks = cticks; //Update the "timer"
		switch(rand()%4)
		{
		case 0:
			direction = DGObject::eUp;
			break;
		case 1:
			direction = DGObject::eDown;
			break;
		case 2:
			direction = DGObject::eLeft;
			break;
		case 3:
			direction = DGObject::eRight;
			break;
		}
	}

//	if(cticks%2)
		return Tank::move(step,obj,direction);
//	return -1;
}

Bullet* Enemy::shoot()
{
	unsigned int cticks = SDL_GetTicks();
	if(cticks > ticksShoot + 1000)
	{
		ticksShoot = cticks;
		return  Tank::shoot();
	}
	return nullptr;
}

