

#include "Flag.h"
#include "../config.h"
Flag::Flag(SDL_Point position):
	GObject(Config::txFlag.h, Config::txFlag.w, position.x, position.y)
{
	setTexture(&Config::txFlag);
}

Flag::Flag(int x, int y):
	GObject(Config::txFlag.h, Config::txFlag.w, x, y)
{
	setTexture(&Config::txFlag);
}

Flag::~Flag()
{

}
