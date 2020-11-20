/**
 * @file	Render.h
 * @author	Santiago Duque
 * @brief 	Class to render textures
 * @date	Nov 19, 2020
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <SDL2/SDL.h>
#include "g_objects/g_object.h"

class Render
{
public:
	Render(SDL_Window *);
	virtual ~Render();

	static void init(SDL_Window *);
	static void drawObject(GObject &object);
	static void drawText();
	static void drawRect(SDL_Rect);

private:
	static SDL_Renderer *render;
};

#endif /* RENDER_H_ */
