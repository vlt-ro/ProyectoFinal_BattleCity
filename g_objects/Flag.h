/*
 * Flag.h
 *
 *  Created on: Nov 22, 2020
 *      Author: santiago
 */

#ifndef G_OBJECTS_FLAG_H_
#define G_OBJECTS_FLAG_H_

#include "g_object.h"

class Flag: public GObject
{
public:
	Flag(int x, int y);
	virtual ~Flag();
};

#endif /* G_OBJECTS_FLAG_H_ */
