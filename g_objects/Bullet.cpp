/*
 * bullet.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: vadd
 */

#include "Bullet.h"
#include <SDL2/SDL.h>
#include "../config.h"
#include "dgobject.h"
#include <map>
#include <iterator>
#include <iostream>
using namespace std;
Bullet::Bullet(int x, int y,int direction):
	DGObject(Config::txBullet[0].h, Config::txBullet[0].w, x, y)
{
	/* load textures */
	for(int i=0; i<4; i++)
		textures[i] = Config::txBullet[i];

	setTexture(&textures[orientation]);
	this ->direction=direction;
}
Bullet::~Bullet() {

}

SDL_Rect Bullet::move(int step, multimap <string, GObject> &objects )
{
	bool move_ = true;
	SDL_Rect dim = getDimension();
	switch(direction)
	{
	case eUp:
		dim.y -= step;
		break;
	case eDown:
		dim.y += step;
		break;
	case eLeft:
		dim.x -= step;
		break;
	case eRight:
		dim.x += step;
		break;
	default:
		move_=false;
	}
	SDL_Rect obstacle={0,0,0,0};
	for (itr = objects.begin(); itr != objects.end(); ++itr)
	{
		if(	collide(dim,itr->second.getDimension()))
		{
			if (itr->first!="concrete")
			{
				obstacle = itr->second.getDimension();
				objects.erase(itr);
			}
			else
			{
				obstacle.w = -1;
			}
			move_ = false;
			break;
		}

	}
	SDL_Rect d = getDimension();
	if ((direction==eUp and d.y-step <= 0) or
		(direction==eDown and d.y + step >= Config::SCREEN_HEIGHT - d.h) or
		(direction==eLeft and d.x-step <= 0) or
		(direction==eRight and (d.x + step) >= (Config::SCREEN_WIDTH - 48 -d.w)))
	{
		obstacle = d;
	}

	DGObject::move(direction, move_? step : 0);
	return obstacle;
}
