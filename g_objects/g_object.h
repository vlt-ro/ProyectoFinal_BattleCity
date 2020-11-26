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
	 * @param height	Altura de la imagen.
	 * @param width		Ancho de la imagen.
	 * @param xPos		Coordenada x desde la esquina superior izquierda.
	 * @param yPos		Coordenada y desde la esquina superior izquierda.
	 */
	GObject(size_t height=0, size_t width=0, int xPos=0, int yPos=0);

	virtual ~GObject(){};

	/**
	 * Establece una nueva posición.
	 */
	void setPosition(int x,int y);

	/**
	 * @return Posición del objeto.
	 */
	SDL_Point getPosition();

	/**
	 * @return Una estructura con la información de la posición y de la
	 * 		   dimension del objeto.
	 */
	SDL_Rect getDimension();

	/**
	 * @return Región donde se encuentra la textura del objeto.
	 */
	const SDL_Rect * getTexture();

	/**
	 * Establece la región donde se encuentra la textura del objeto.
	 */
	void setTexture(const SDL_Rect *texture);

	/**
	 * @return Obtiene el ID del objeto.
	 */
	unsigned getID();

private:
	unsigned id;
	SDL_Rect rect; // Posición y dimensión del objeto.
	SDL_Rect texture; // Posición y dimensión de la textura.

protected:
	/**
	 * Establece el ID del objeto.
	 */	
	void setID(unsigned);
};

#endif /* GOBJECT_H_ */
