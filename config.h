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

    static const int UN; 
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

    /* Región donde se encuentran las texturas de los objetos */
    static const SDL_Rect txBrick;
    static const SDL_Rect txConcrete;
    static const SDL_Rect txFlag;
    static const SDL_Rect txDestroyedFlag;
    static const SDL_Rect txAlly[];
    static const SDL_Rect txEnemy[];
    static const SDL_Rect txBullet[];

    /* ID de los objetos */
    enum {BRICK=1,CONCRETE,FLAG,BULLET,ENEMY,ALLY};
};



#endif /* CONFIG_H_ */
