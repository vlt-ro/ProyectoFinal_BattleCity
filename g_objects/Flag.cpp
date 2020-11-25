

#include "Flag.h"
#include "../config.h"

Flag::Flag(int x, int y):
	GObject(Config::txFlag.h, Config::txFlag.w, x, y)
{
	setTexture(&Config::txFlag);
	setID(Config::FLAG);
}

Flag::~Flag()
{

}
