/*
 * Tank.cpp
 *
 *  Created on: Nov 24, 2020
 *      Author: vadd
 */

#include "Tank.h"

Tank::Tank(size_t height, size_t width, int xPos, int yPos):
	  DGObject(height, width, xPos, yPos)
{
}

Tank::~Tank() {}

Bullet* Tank::shoot()
{
	Bullet *b = nullptr;
	auto d = getDimension();

	switch(orientation)
	{
	case eUp:
		b = new Bullet(d.x+12, d.y+5, eUp);
		break;
	case eDown:
		b = new Bullet(d.x+12, d.y+d.h-5, eDown);
		break;
	case eLeft:
		b = new Bullet(d.x+5, d.y+12, eLeft);
		break;
	case eRight:
		b = new Bullet(d.x+d.w-5, d.y+12, eRight);
		break;
	}

	return b;
}

