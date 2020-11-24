/*
 * Render.cpp
 *
 *  Created on: Nov 19, 2020
 *      Author: santiago
 */

#include "Render.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "config.h"

using std::string;

SDL_Renderer* Render::render = nullptr;
SDL_Texture* Render::texture = nullptr;

const SDL_Color Render::red = {0xFF, 0x33, 0x33, SDL_ALPHA_OPAQUE};
const SDL_Color Render::white = {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE};
const SDL_Color Render::black = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
const SDL_Color Render::gray = {0x60, 0x60, 0x60, SDL_ALPHA_OPAQUE};

Render::Render(SDL_Window *window)
{

}

Render::~Render()
{
	SDL_DestroyRenderer(render);
}

void Render::init(SDL_Window * window)
{
	// Initialize the render
	if(!render)
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!render)
	{
		string s = string("Renderer could not be created! SDL Error: ") +=
				   string(SDL_GetError());
		throw s;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		string s = string("SDL_image could not initialize! SDL_image Error: ") +
				   string(IMG_GetError());
		throw s;
	}

	//Initialize font
	if( TTF_Init()==-1 )
	{
		string s = string("TTF_Init could not initialize! SDL_ttf Error: ")+
				   string(TTF_GetError());
		throw s;
	}

	if(!texture)
		texture = loadTexture(Config::path_global_texture);
}


SDL_Texture* Render::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		string s = string("Unable to create texture from:")+
				   string(path.c_str());
		throw s;
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(render, loadedSurface);

		if( newTexture == NULL )
		{
			string s = string("Unable to create texture from:")+
					   string(path.c_str());
			throw s;
	    }

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}


void Render::drawObject(int ObjectXPosition, int ObjectYPosition, int ObjectWidth, int ObjectHeight, SDL_Texture* Texture)
{
	SDL_Rect RectangleObject = {ObjectXPosition, ObjectYPosition, ObjectWidth, ObjectHeight};

    SDL_RenderCopy(render, Texture, NULL, &RectangleObject);
}

void Render::drawObject(const SDL_Rect *source, int x, int y)
{
	SDL_Rect dest = {x, y, source->w, source->h};
	SDL_RenderCopy(render,texture,source,&dest);
}

void Render::drawText(int TextXPosition, int TextYPosition, int TextWidth, int TextHeight, SDL_Color TextColor, string FontName, int FontSize, string Text )
{
	SDL_Rect RectangleText = {TextXPosition, TextYPosition, TextWidth, TextHeight};
	SDL_Texture* TextTexture = nullptr;
	SDL_Surface* TextSurface = nullptr;
	TTF_Font* Font = TTF_OpenFont(FontName.c_str(), FontSize);

	if(Font == nullptr)
	{
		string s = string("SDL_ttf could not open the font! SDL_ttf Error: %s\n")+
				   string(TTF_GetError());
		throw s;
	}

	TextSurface = TTF_RenderText_Solid(Font, Text.c_str(), TextColor);

	TextTexture = SDL_CreateTextureFromSurface(render, TextSurface);

	SDL_RenderCopy(render, TextTexture, NULL, &RectangleText);
}

void Render::drawRect(int RectangleXPosition, int RectangleYPosition, int RectangleWidth, int RectangleHeight, SDL_Color RectangleColor, bool Filled)
{
	// Create the rectangle to render
	SDL_Rect Rectangle = {RectangleXPosition, RectangleYPosition, RectangleWidth, RectangleHeight};

	// Set the rectangle color
	SDL_SetRenderDrawColor(render, RectangleColor.r, RectangleColor.g, RectangleColor.b, RectangleColor.a);

	// Render a filled rectangle
	if(Filled)
		SDL_RenderFillRect(render, &Rectangle);

	// Render a unfilled rectangle
	else
		SDL_RenderDrawRect(render, &Rectangle);
}

void Render::drawRect(SDL_Rect rect, SDL_Color RectangleColor, bool Filled)
{
	drawRect(rect.x, rect.y, rect.w, rect.h, RectangleColor, Filled);
}

void Render::presentRender()
{
	SDL_RenderPresent( render );
}

/*bool Render::collide(SDL_Rect rect1, SDL_Rect rect2)
{
    SDL_Rect intersect_rect;

    intersect_rect.x = std::max(rect1.x, rect2.x);
    intersect_rect.y = std::max(rect1.y, rect2.y);
    intersect_rect.w = std::min(rect1.x + rect1.w, rect2.x + rect2.w) - intersect_rect.x;
    intersect_rect.h = std::min(rect1.y + rect1.h, rect2.y + rect2.h) - intersect_rect.y;

    if(intersect_rect.w > 0 && intersect_rect.h > 0)
    	return true;
    return false;
}*/
