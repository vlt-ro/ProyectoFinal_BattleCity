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

using std::string;

SDL_Renderer* Render::render = nullptr;

Render::Render(SDL_Window *window)
{
	// Initialize the render
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
		string s = string("TTF_Init could not initialize! SDL_ttf Error: %s\n")+
				   string(TTF_GetError());
		throw s;
	}

}

Render::~Render()
{
	SDL_DestroyRenderer(render);
}

void Render::init(SDL_Window * window)
{
	// Initialize the render
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
		string s = string("TTF_Init could not initialize! SDL_ttf Error: %s\n")+
				   string(TTF_GetError());
		throw s;
	}
}

void Render::drawObject(GObject&)
{

}

void Render::drawText()
{

}

void Render::drawRect(SDL_Rect)
{

}

