/**
 * @file	tank.h
 * @author	Santiago Duque
 * @brief 	Base class of dynamic graphic objects
 * @date	Nov 22, 2020
 */
#ifndef G_OBJECTS_DGOBJECT_H_
#define G_OBJECTS_DGOBJECT_H_

#include "g_object.h"
#include <map>
#include <iterator>
#include <SDL2/SDL.h>
using namespace std;

class DGObject: public GObject
{
public:

	enum{eUp=0, eDown=1, eLeft=2, eRight=3};

	DGObject(int h, int w, int x, int y);
	virtual ~DGObject();

	void move(int step);
	void move(int direction, int step);
	void move(int direction, int step, multimap <string, GObject> objects );
	//bool collide(SDL_Rect *rect);
	bool collide(SDL_Rect rect1, SDL_Rect rect2);


protected:
	SDL_Rect textures[4]; //Up, down, left and right orientation textures
	int orientation = 10;
	multimap <string, GObject> :: iterator itr;
};

#endif /* G_OBJECTS_DGOBJECT_H_ */
