/*
 * Brick.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: santiago
 */

#include "Brick.h"
#include "../config.h"

Brick::Brick(int x, int y):
		GObject(Config::txBrick.h, Config::txBrick.w, x, y)
{
	setTexture(&Config::txBrick);
	setID(Config::BRICK);
}

Brick::~Brick()
{

}

