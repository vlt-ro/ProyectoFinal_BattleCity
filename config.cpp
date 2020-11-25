/*
 * config.cpp
 *
 *  Created on: Nov 20, 2020
 *      Author: vadd
 */
#include "config.h"
#include <string>

using std::string;

const int Config::UN = 16;
const int Config::SCREEN_WIDTH = 29*UN;
const int Config::SCREEN_HEIGHT = 26*UN;
const string Config::textureMainMenu = "resources/texturasMainMenu.txt";
const string Config::textureMainMenu_names = "resources/texturasMainMenu_names.txt";
const string Config::textureGame = "resources/texturasGame.txt";
const string Config::textureGame_names = "resources/texturasGame_names.txt";
const string Config::mapLevel1 = "resources/mapa.csv";
const string Config::font_tank = "resources/fonts/tank_font.ttf";
const string Config::font_prstartk = "resources/fonts/prstartk.ttf";
const string Config::path_global_texture = "resources/img/texture.png";

/* Objects "textures" */
const SDL_Rect Config::txBrick = {29*UN*2, 0, UN, UN};
const SDL_Rect Config::txConcrete = {29*UN*2, 9*UN, UN, UN};
const SDL_Rect Config::txFlag = {59*UN,0,2*UN,2*UN};
const SDL_Rect Config::txDestroyedFlag = {59*UN,32,32,32};
const SDL_Rect Config::txAlly[] = { {40*UN, 0, 32, 32}, //UP
									{44*UN, 0, 32, 32}, //Down
									{46*UN, 0, 32, 32}, //Left
									{42*UN, 0, 32, 32}};//Right
const SDL_Rect Config::txEnemy[] = { {8*UN,  0, 32, 32}, //UP
									 {12*UN, 0, 32, 32}, //Down
									 {14*UN, 0, 32, 32}, //Left
									 {10*UN, 0, 32, 32}};//Right
const SDL_Rect Config::txBullet[] = { {945, 128, 8, 8}, //UP
									  {961, 128, 8, 8}, //Down
									  {968, 128, 8, 8}, //Left
									  {952, 128, 8, 8}};//Right
