/**
 * @file	tank.h
 * @author	Santiago Duque
 * @brief 	Base class of dynamic graphic objects
 * @date	Nov 22, 2020
 */
#ifndef G_OBJECTS_DGOBJECT_H_
#define G_OBJECTS_DGOBJECT_H_

#include "g_object.h"
#include <map>
#include <vector>
#include <iterator>
#include <SDL2/SDL.h>
using namespace std;

class DGObject: public GObject
{
public:

	enum{eUp=0, eDown=1, eLeft=2, eRight=3};

	DGObject(int h, int w, int x, int y);
	virtual ~DGObject();

	/**
	 * Mueve el objeto step píxeles en la dirección predeterminada
	 */
	int move(int step);

	/**
	 * Mueve el objeto step píxeles y modifica la dirección
	 */
	int move(int direction, int step);

	/**
	 * @brief Mueve el objeto step píxeles, modifica la dirección en caso de
	 * no colisionar con ningún objeto del vector obj.
	 * @return -1: Si no choca con ningún objeto. En otro retorna el índice
	 *         en el que se encuentra el objeto con qué colisiona.
	 */
	int move(int step, vector<GObject*> &obj, int direction =-1);

	/**
	 * Revisa si el objeto de la clase se intersecta con rect.
	 */	
	bool collide(SDL_Rect rect);

	/**
	 * Revisa si rect1 y rect2 se intersectan.
	 */
	bool collide(SDL_Rect rect1, SDL_Rect rect2);

protected:

	SDL_Rect textures[4]; //Orientaciones de las texturas: 
						  //Arriba, abajo, izquierda, derecha
	int orientation; // Orientación actual del objeto.

private:

	/**
	 * Mueve un rectángulo evitando que choque con los bordes.
	 */
	static SDL_Rect moveRect(SDL_Rect rect, int step, int orientation);
};

#endif /* G_OBJECTS_DGOBJECT_H_ */
