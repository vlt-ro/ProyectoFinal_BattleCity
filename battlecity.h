/**
 * @author 
 * @brief  
 */

#include <vector>
#include "states/state.h"
#include <SDL2/SDL.h>


class BattleCity
{
public :

  BattleCity();
  ~BattleCity();

  /**
   * Inicia y controla el estado del juego y los eventos del teclado. 
   */
  void start();

private :   

  State *currState; //Estado actual
  SDL_Window *window; // Ventana del juego

  /**
   * Inicia las librerías de SDL y la ventana
   */
  bool init();

};

