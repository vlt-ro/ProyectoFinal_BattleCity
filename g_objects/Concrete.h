/*
 * Concrete.h
 *
 *  Created on: Nov 21, 2020
 *      Author: santiago
 */

#ifndef G_OBJECTS_CONCRETE_H_
#define G_OBJECTS_CONCRETE_H_

#include "g_object.h"

class Concrete: public GObject
{
public:
	Concrete(int x, int y);
	virtual ~Concrete();
};

#endif /* G_OBJECTS_CONCRETE_H_ */
