/*
 * config.h
 *
 *  Created on: Nov 20, 2020
 *      Author: vadd
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <SDL2/SDL.h>

using std::string;

class Config{

public:

    static const int UN;  //Número minimo de pixeles
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const string textureMainMenu;
    static const string textureMainMenu_names;
    static const string textureGame;
    static const string textureGame_names;
    static const string mapLevel1;
    static const string font_tank;
    static const string font_prstartk;
    static const string path_global_texture;

    /* Objects "textures" */
    static const SDL_Rect txBrick;
    static const SDL_Rect txConcrete;
    static const SDL_Rect txFlag;
    static const SDL_Rect txAlly[];
    static const SDL_Rect txEnemy;
};



#endif /* CONFIG_H_ */
