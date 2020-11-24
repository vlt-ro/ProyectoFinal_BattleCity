/**
 * @file	GraphicElement.cpp
 * @author	Santiago Duque
 * @date	Nov 13, 2020
 */

#include "g_object.h"

GObject::GObject(size_t height, size_t width, int xPos, int yPos)
{
	rect.h = height;
	rect.w = width;
	rect.x = xPos;
	rect.y = yPos;
	texture = {0,0,0,0};
}

GObject::GObject(SDL_Rect rect)
{
	this->rect = rect;
	texture = {0,0,0,0};
}

void GObject::setPosition(int x,int y)
{
	rect.x = x;
	rect.y = y;
}

SDL_Point GObject::getPosition()
{
	SDL_Point p;
	p.x = rect.x;
	p.y = rect.y;
	return p;
}

SDL_Rect GObject::getDimension()
{
	return rect;
}

const SDL_Rect* GObject::getTexture()
{
	return &texture;
}
void GObject::setTexture(const SDL_Rect *texture)
{
	this->texture = *texture;
}






