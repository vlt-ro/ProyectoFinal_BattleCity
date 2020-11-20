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
   * @brief Imprime las reglas del juego
   */
  void gameRules();

  /**
   * @brief Ejecuta el juego
   */  
  void playLevel1();

  /**
   * @brief Menu en el que el usario puede decidir jugar o leer las reglas
   */
  void mainMenu();

  void start();

  void closeGraphics();

private :   

  State *currState; //Current state
  SDL_Window *window; //Game window

  /**
   * Starts up SDL and creates window
   */
  bool init();

};

