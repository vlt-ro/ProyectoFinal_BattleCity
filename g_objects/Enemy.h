#ifndef G_OBJECTS_ENEMY_H_
#define G_OBJECTS_ENEMY_H_

#include "dgobject.h"

class Enemy: public DGObject
{
public:
	Enemy(int x, int y);
	virtual ~Enemy();

};

#endif /* G_OBJECTS_ENEMY_H_ */
