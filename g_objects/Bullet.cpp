/*
 * bullet.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: vadd
 */

#include "Bullet.h"
#include <SDL2/SDL.h>
#include "../config.h"
#include "dgobject.h"
#include <map>
#include <iterator>
#include <iostream>
using namespace std;
Bullet::Bullet(int x, int y,int direction):
	DGObject(Config::txBullet[0].h, Config::txBullet[0].w, x, y)
{
	/* load textures */
	for(int i=0; i<4; i++)
		textures[i] = Config::txBullet[i];

	orientation = direction;
	setTexture(&textures[orientation]);
	setID(Config::BULLET);
}
Bullet::~Bullet() {

}

