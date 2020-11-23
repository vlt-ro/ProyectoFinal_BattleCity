/*
 * tank.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: santiago
 */

#include "dgobject.h"
#include "../config.h"
#include <SDL2/SDL.h>

DGObject::DGObject(int h, int w, int x, int y):
	GObject(h, w, x, y)
{
	orientation = eUp;
}

DGObject::~DGObject()
{
}

void DGObject::move(int step)
{
	SDL_Rect d = getDimension();

	switch(orientation)
	{
	case eUp:
		if(d.y-step >= 0)
			setPosition(d.x, d.y - step);
		break;
	case eDown:
		if(d.y + step <= Config::SCREEN_HEIGHT - d.h)
			setPosition(d.x, d.y + step);
		break;
	case eLeft:
		if(d.x-step >= 0)
			setPosition(d.x-step, d.y);
		break;
	case eRight:
		//TODO: if(...)
		setPosition(d.x+step, d.y);
		break;
	}
}

void DGObject::move(int dir, int step)
{
	if(dir != orientation)
	{
		if(dir==eUp || dir==eDown || dir==eLeft || dir==eRight)
		{
			setTexture(&textures[dir]);
			orientation = dir;
		}
		else
			return;
	}

	move(step);
}

