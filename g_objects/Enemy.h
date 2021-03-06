#ifndef G_OBJECTS_ENEMY_H_
#define G_OBJECTS_ENEMY_H_

#include "Tank.h"

class Enemy: public Tank
{
public:
	Enemy(int x, int y);
	virtual ~Enemy(){};
	int move(int step, vector<GObject*> &obj, int direction =-1);

	Bullet* shoot();

private:
	unsigned int ticks;
	unsigned int ticksShoot;
	static bool isSeedInitilized;
};

#endif /* G_OBJECTS_ENEMY_H_ */
