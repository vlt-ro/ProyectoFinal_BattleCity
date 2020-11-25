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

	virtual ~GObject(){}; // to avoid bad performance while deleting a derived object

	/**
	 * Set a new position
	 */
	void setPosition(int x,int y);

	/**
	 * return the current position of the graphic element
	 */
	SDL_Point getPosition();

	/**
	 * Return an structure with the position and dimension
	 * information
	 */
	SDL_Rect getDimension();

	const SDL_Rect * getTexture();
	void setTexture(const SDL_Rect *texture);

	unsigned getID();

private:
	unsigned id;
	SDL_Rect rect; //rectangle with  dimension and position information
	SDL_Rect texture; // Really it's not a texture

protected:
	void setID(unsigned);
};

#endif /* GOBJECT_H_ */
