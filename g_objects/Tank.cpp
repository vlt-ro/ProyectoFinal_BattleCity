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
		b = new Bullet(d.x+9, d.y+9, eUp);
		break;
	case eDown:
		b = new Bullet(d.x+9, d.y+9, eDown);
		break;
	case eLeft:
		b = new Bullet(d.x+9, d.y+9, eLeft);
		break;
	case eRight:
		b = new Bullet(d.x+9, d.y+9, eRight);
		break;
	}

	return b;
}

