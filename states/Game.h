/*
 * Game.h
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#ifndef STATES_GAME_H_
#define STATES_GAME_H_

#include "state.h"

class Game: public State
{
public:
	Game();
	virtual ~Game();

	// Inherit methods
	void inputKey(char key);
	int task();
	bool start();
	bool stop();


private:
};

#endif /* STATES_GAME_H_ */
