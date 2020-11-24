/*
 * Tank.h
 *
 *  Created on: Nov 24, 2020
 *      Author: vadd
 */

#ifndef G_OBJECTS_TANK_H_
#define G_OBJECTS_TANK_H_

#include "dgobject.h"
#include "Bullet.h"

class Tank: public DGObject
{
public:
	Tank(size_t height, size_t width, int xPos, int yPos);
	virtual ~Tank();

	Bullet* shoot();
};

#endif /* G_OBJECTS_TANK_H_ */
