/*
 * tank.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: santiago
 */

#include "dgobject.h"
#include "../config.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <map>
#include <iterator>
#include <iostream>
using namespace std;

DGObject::DGObject(int h, int w, int x, int y):
	GObject(h, w, x, y)
{
	orientation = eUp;
}

DGObject::~DGObject()
{
}

bool DGObject::move(int step)
{
	bool r = false;
	SDL_Rect d = getDimension();

	switch(orientation)
	{
	case eUp:
		if(d.y-step >= 0)
		{
			setPosition(d.x, d.y - step);
			r = true;
		}
		break;
	case eDown:
		if(d.y + step <= Config::SCREEN_HEIGHT - d.h)
		{
			setPosition(d.x, d.y + step);
			r = true;
		}
		break;
	case eLeft:
		if(d.x-step >= 0)
		{
			setPosition(d.x-step, d.y);
			r = true;
		}
		break;
	case eRight:
		if((d.x + step) <= (Config::SCREEN_WIDTH - 48 -d.w))
		{
			setPosition(d.x+step, d.y);
			r = true;
		}
		break;
	}

	return r;
}

bool DGObject::move(int dir, int step)
{
	if(dir != orientation)
	{
		if(dir==eUp || dir==eDown || dir==eLeft || dir==eRight)
		{
			setTexture(&textures[dir]);
			orientation = dir;
		}
		else
			return false;
	}

	return move(step);
}


bool DGObject::move(int direction, int step, multimap <string, GObject> &objects )
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
		dim.x -=step;
		break;
	case eRight:
		dim.x += step;
		break;
	default:
		move_ = false;
	}

	for (itr = objects.begin(); itr != objects.end(); ++itr)
	{
		if(	collide(dim,itr->second.getDimension()))
		{
			move_ = false;
			break;
		}
	}

	return move(direction, move_? step : 0);
}

bool DGObject::collide(SDL_Rect rect1, SDL_Rect rect2)
{
    SDL_Rect intersect_rect;

    intersect_rect.x = std::max(rect1.x, rect2.x);
    intersect_rect.y = std::max(rect1.y, rect2.y);
    intersect_rect.w = std::min(rect1.x + rect1.w, rect2.x + rect2.w) - intersect_rect.x;
    intersect_rect.h = std::min(rect1.y + rect1.h, rect2.y + rect2.h) - intersect_rect.y;

    if(intersect_rect.w > 0 && intersect_rect.h > 0)
    	return true;
    return false;
}

bool DGObject::collide(SDL_Rect rect)
{
   return collide(getDimension(), rect);
}

