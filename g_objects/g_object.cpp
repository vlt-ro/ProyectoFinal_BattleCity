/**
 * @file	GraphicElement.cpp
 * @author	Santiago Duque
 * @date	Nov 13, 2020
 */

#include <iostream>
#include "g_object.h"

GObject::GObject(size_t height, size_t width, int xPos, int yPos)
{
	rect.h = height;
	rect.w = width;
	rect.x = xPos;
	rect.y = yPos;
	this->image = nullptr;

	std::cout << "GraphicElement constructor " <<height<<width<<xPos<<yPos << std::endl;
}

GObject::GObject(SDL_Rect rect)
{
	this->rect = rect;
	this->image = nullptr;
}

void GObject::draw()
{

}

void GObject::del()
{

}

bool GObject::setPosition(SDL_Point pos)
{
	return false;
}

SDL_Point GObject::getPosition()
{
	SDL_Point p;
	p.x = rect.x;
	p.y = rect.y;
	return p;
}






