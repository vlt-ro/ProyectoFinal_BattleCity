/*
 * Concrete.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: santiago
 */

#include "Concrete.h"
#include "../config.h"

Concrete::Concrete(SDL_Point position):
		GObject(Config::txConcrete.h, Config::txConcrete.w, position.x, position.y)
{
	setTexture(&Config::txConcrete);
}

Concrete::Concrete(int x, int y):
				GObject(Config::txConcrete.h, Config::txConcrete.w, x, y)
{
	setTexture(&Config::txConcrete);
}

Concrete::~Concrete()
{
}

