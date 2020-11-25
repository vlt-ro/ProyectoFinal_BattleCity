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
	ticksShoot = ticks+1000;
}

int Enemy::move(int step, vector<GObject*> &obj, int direction)
{
	const SDL_Point target_position={13*Config::UN,25*Config::UN};
	unsigned int cticks = SDL_GetTicks();
    float p = static_cast<float>(rand()) / RAND_MAX;

	if(cticks > ticks)
	{
		ticks = cticks + rand()%800 + 100; //Update the "timer"
		if(p < 0.8  && target_position.x > 0 && target_position.y > 0)
		{
			int dx = target_position.x - (getPosition().x + getDimension().w / 2);
			int dy = target_position.y - (getPosition().y + getDimension().h / 2);

			p = static_cast<float>(rand()) / RAND_MAX;

			if(abs(dx) > abs(dy))
				direction = p < 0.7 ? (dx < 0 ? eLeft : eRight) : (dy < 0 ? eUp : eDown);
			else
				direction = p < 0.7 ? (dy < 0 ? eUp : eDown) : (dy < 0 ? eLeft : eRight);
		}
		else
			direction = rand() % 4;
	}
	else
		direction = orientation;

	return Tank::move(step,obj,direction);
}

Bullet* Enemy::shoot()
{
	unsigned int cticks = SDL_GetTicks();
	if(cticks > ticksShoot)
	{
		ticksShoot = cticks + rand()%2000 + 1000;
		return  Tank::shoot();
	}
	return nullptr;
}

