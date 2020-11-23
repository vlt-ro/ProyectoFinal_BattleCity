/*
 * Brick.h
 *
 *  Created on: Nov 21, 2020
 *      Author: santiago
 */

#ifndef G_OBJECTS_BRICK_H_
#define G_OBJECTS_BRICK_H_

#include "g_object.h"
#include <SDL2/SDL.h>

class Brick: public GObject
{
public:
	Brick(SDL_Point position);
	Brick(int x, int y);
	virtual ~Brick();
};

#endif /* G_OBJECTS_BRICK_H_ */
