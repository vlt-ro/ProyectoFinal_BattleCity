/**
 * @file	GraphicElement.h
 * @author	Santiago Duque
 * @brief 	Basis class for all graphics elements
 * @date	Nov 13, 2020
 */

#ifndef GOBJECT_H_
#define GOBJECT_H_

#include <cstdlib>
#include <SDL2/SDL.h>

using std::size_t;

class GObject
{
public:

	/**
	 * @param height	Image height
	 * @param width		Image width
	 * @param xPos		x coordinate of the image center
	 * @param yPos		y coordinate of the image center
	 */
	GObject(size_t height=0, size_t width=0, int xPos=0, int yPos=0);

	/**
	 * @param rect	Rectangle with the position and dimension
	 * 				information of the new graphic element object
	 */
	GObject(SDL_Rect rect);

	virtual ~GObject(){}; // to avoid bad performance while deleting a derived object

	void draw();

	void del();

	/**
	 * Try to set a new position
	 * @param pos	Point with the position information
	 * @return true if the new position could be
	 * 		   setted, false otherwise.
	 */
	bool setPosition(SDL_Point pos);

	/**
	 * return the current position of the graphic element
	 */
	SDL_Point getPosition();

protected:
	SDL_Rect rect; //rectangle with  dimension and position information

	const void *image; // TODO: change to the correct pointer type

};

#endif /* GOBJECT_H_ */
