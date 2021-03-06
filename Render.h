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
	static void drawObject(int ObjectXPosition, int ObjectYPosition, int ObjectWidth, int ObjectHeight, SDL_Texture* Texture);
	static void drawObject(const SDL_Rect *source, int x, int y);
	static void drawText(int TextXPosition, int TextYPosition, int TextWidth, int TextHeight, SDL_Color TextColor, string FontName, int FontSize, string Text);
	static void drawRect(int RectangleXPosition, int RectangleYPosition, int RectangleWidth, int RectangleHeight, SDL_Color RectangleColor, bool Filled);
	static void drawRect(SDL_Rect rect, SDL_Color RectangleColor, bool Filled);
	static void presentRender();

	static void close();

	static const SDL_Color red; 
	static const SDL_Color white; 
	static const SDL_Color black; 
	static const SDL_Color gray; 

private:
	static SDL_Renderer *render;
	static SDL_Texture *texture;
};

#endif /* RENDER_H_ */
