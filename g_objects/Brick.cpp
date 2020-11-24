/*
 * Brick.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: santiago
 */

#include "Brick.h"
#include "../config.h"

Brick::Brick(SDL_Point position):
		GObject(Config::txBrick.h, Config::txBrick.w, position.x, position.y)
{
	setTexture(&Config::txBrick);
}

Brick::Brick(int x, int y):
		GObject(Config::txBrick.h, Config::txBrick.w, x, y)
{
	setTexture(&Config::txBrick);
}

Brick::~Brick()
{

}

