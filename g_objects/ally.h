/*
 * ally.h
 *
 *  Created on: Nov 22, 2020
 *      Author: santiago
 */

#ifndef G_OBJECTS_ALLY_H_
#define G_OBJECTS_ALLY_H_

#include "Tank.h"

class Ally: public Tank
{
public:
	Ally(int x, int y);
	virtual ~Ally();
};

#endif /* G_OBJECTS_ALLY_H_ */
