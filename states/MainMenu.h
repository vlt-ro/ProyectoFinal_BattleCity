/*
 * MainMenu.h
 *
 *  Created on: Nov 18, 2020
 *      Author: santiago
 */

#ifndef STATES_MAINMENU_H_
#define STATES_MAINMENU_H_

#include "state.h"

class MainMenu: public State
{
public:
	MainMenu();
	virtual ~MainMenu();

	// Inherit methods
	void inputKey(char key);
	int task();
	bool start();
	bool stop();
};

#endif /* STATES_MAINMENU_H_ */
