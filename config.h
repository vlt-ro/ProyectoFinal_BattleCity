/*
 * config.h
 *
 *  Created on: Nov 20, 2020
 *      Author: vadd
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

using std::string;

class Config{

public:

    static const int UN;  //Numero minimo de pixeles
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const string textureMainMenu;
    static const string textureMainMenu_names;
    static const string textureGame;
    static const string textureGame_names;
    static const string mapLevel1;
    static const string font_tank;
    static const string font_prstartk;
};



#endif /* CONFIG_H_ */
