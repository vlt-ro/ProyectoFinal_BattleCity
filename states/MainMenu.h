/*
 * MainMenu.h
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#ifndef STATES_MAINMENU_H_
#define STATES_MAINMENU_H_

#include "state.h"
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using namespace std;

class MainMenu: public State
{
public:

	/**
	 * Eventos que serán retornados por método task.
	 */
	enum
	{
		eONE_PLAYER = 0x01,///< Modo: un jugador
		eTWO_PLAYERS,      ///< Modo: dos jugadores
		eEXIT              ///< Salir del juego
	};

	MainMenu();
	virtual ~MainMenu();

	void inputKey(string key);
	int task();
	bool start();
	bool stop();

private:

    map<string, SDL_Texture*> texturaMainMenu;
    int yPos;
    int counter;
    string currKey="";
};

#endif /* STATES_MAINMENU_H_ */
