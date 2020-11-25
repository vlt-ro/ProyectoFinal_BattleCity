/*
 * Concrete.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: santiago
 */

#include "Concrete.h"
#include "../config.h"


Concrete::Concrete(int x, int y):
				GObject(Config::txConcrete.h, Config::txConcrete.w, x, y)
{
	setTexture(&Config::txConcrete);
	setID(Config::CONCRETE);
}

Concrete::~Concrete()
{
}

