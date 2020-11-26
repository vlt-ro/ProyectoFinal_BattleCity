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
	 * Pasa el indicador de la tecla presionada.
	 */
	virtual void inputKey(string key) = 0;

	/**
	 * @brief Tarea del estado actual.
	 * @note Debe de ser llamada periodicamente.	
	 */
	virtual int task() = 0;

	/**
	 * Inicializa el estado
	 */
	virtual bool start() = 0;

	/**
	 * Detiene el estado y libera memoria
	 */
	virtual bool stop() = 0;

};
#endif /* STATES_STATE_H_ */