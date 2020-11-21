/**
 * @file	state.h
 * @author	Santiago Duque
 * @brief 	Base class of game states
 * @date	Nov 18, 2020
 */

#ifndef STATES_STATE_H_
#define STATES_STATE_H_

#include <string>

using std::string;

class State
{
public:

	virtual ~State(){};

	/**
	 * @brief Pass a character to take decisions. This method
	 * 		  is useful to pass characters read from the keyboard.
	 * @param key
	 */
	virtual void inputKey(string key) = 0;

	//TODO: The next functions must be changed to a thread
	/**
	 * Main task of the state
	 */
	virtual int task() = 0;

	/**
	 * Starts (re-starts) the state
	 */
	virtual bool start() = 0;

	/**
	 * Stop the state and clean resources
	 */
	virtual bool stop() = 0;

};




#endif /* STATES_STATE_H_ */
