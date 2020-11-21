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
#include <string>

using std::string;
class Render
{
public:
	Render(SDL_Window *);
	virtual ~Render();

	static void init(SDL_Window *);
	static SDL_Texture* loadTexture(std::string path);
	//static void drawObject(GObject &object);
	static void drawObject(int ObjectXPosition, int ObjectYPosition, int ObjectWidth, int ObjectHeight, SDL_Texture* Texture);
	static void drawText(int TextXPosition, int TextYPosition, int TextWidth, int TextHeight, SDL_Color TextColor, string FontName, int FontSize, string Text);
	static void drawRect(int RectangleXPosition, int RectangleYPosition, int RectangleWidth, int RectangleHeight, SDL_Color RectangleColor, bool Filled);
	static void presentRender();

	static const SDL_Color red; //Red
	static const SDL_Color white; //Red
	static const SDL_Color black; //Red
	static const SDL_Color gray; //Red

private:
	static SDL_Renderer *render;
};

#endif /* RENDER_H_ */
