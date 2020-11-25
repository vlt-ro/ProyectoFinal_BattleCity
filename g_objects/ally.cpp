/*
 * ally.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: santiago
 */

#include "ally.h"
#include "../config.h"

Ally::Ally(int x, int y):
	Tank(Config::txAlly[0].h, Config::txAlly[0].w, x, y)
{
	/* load textures */
	for(int i=0; i<4; i++)
		textures[i] = Config::txAlly[i];
	orientation = eUp;
	setTexture(&textures[eUp]);
	setID(Config::ALLY);
}

Ally::~Ally()
{
}

