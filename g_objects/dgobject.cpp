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

int DGObject::move(int step)
{
	bool r = false;
	SDL_Rect d = moveRect(getDimension(), step, orientation);
	if(d.x != getPosition().x || d.y != getPosition().y)
	{
		setPosition(d.x, d.y);
		r = true;
	}
	return r;
}

int DGObject::move(int dir, int step)
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

int DGObject::move(int step, vector<GObject*> &obj, int dir)
{
	int r = -1;

	if(dir != orientation)
	{
		if(dir==eUp || dir==eDown || dir==eLeft || dir==eRight)
		{
			setTexture(&textures[dir]);
			orientation = dir;
		}
	}


	SDL_Rect d = moveRect(getDimension(), step, orientation);
	if(d.x != getPosition().x || d.y != getPosition().y)
	{
		for( auto it=obj.begin(); it<obj.end(); it++ )
		{
			if(collide(d, (*it)->getDimension()) && (this != (*it)))
				return it - obj.begin();
		}
		setPosition(d.x, d.y);
	}
	return r;
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

SDL_Rect DGObject::moveRect(SDL_Rect rect, int step, int orientation)
{
	switch(orientation)
	{
	case eUp:
		if(rect.y-step >= 0)
			rect.y -= step;
		break;
	case eDown:
		if(rect.y + step <= Config::SCREEN_HEIGHT - rect.h)
			rect.y += step;
		break;
	case eLeft:
		if(rect.x-step >= 0)
			rect.x -= step;
		break;
	case eRight:
		if((rect.x + step) <= (Config::SCREEN_WIDTH - 48 -rect.w))
			rect.x += step;
		break;
	}
	return rect;
}

