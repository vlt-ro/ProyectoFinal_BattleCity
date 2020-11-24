#ifndef G_OBJECTS_ENEMY_H_
#define G_OBJECTS_ENEMY_H_

#include "Tank.h"

class Enemy: public Tank
{
public:
	Enemy(int x, int y);
	virtual ~Enemy();

};

#endif /* G_OBJECTS_ENEMY_H_ */
