/*
 * bullet.h
 *
 *  Created on: Nov 23, 2020
 *      Author: vadd
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "dgobject.h"
#include <SDL2/SDL.h>
#include <map>
#include <iterator>
#include <iostream>
using namespace std;
class Bullet: public DGObject
{
public:
	Bullet(int x, int y,int direction);
	SDL_Rect move(int step, multimap <string, GObject> &objects );
	virtual ~Bullet();
protected:
	int direction = -1;
};
#endif /* BULLET_H_ */

