#ifndef __CONECTA4_H__
#define __CONECTA4_H__

#include "tablero.h"
#include "ArbolGeneral.h"
#include <cstdlib> //rand()
#include <utility> //pair

/******************************************************************************/
/**
 * @brief TDA Conecta4
 * 
 * Este TDA sirve para almacenar los tableros posibles generados a partir de un
 * tablero inicial. Además, proporciona los métodos para actualizar dichos 
 * tableros y escoger, según diferentes perspectivas, el mejor para el jugador automático
 */
class Conecta4 {
 private:
  ArbolGeneral<Tablero> arbol_posibilidades; ///< Árbol que almacena los tableros
  int metrica_elegida; ///< Número de métrica que evaluará los tableros
  const int MAX_DEPTH = 3; ///< Número de niveles a comprobar
 
 public:
  /**
   * @brief Constructor
   * @param tab Tablero inicial
   * @param met Métrica a utilizar durante la partida
   */
  Conecta4(const Tablero& tab, int met);

  /**
   * @brief Devuelve el árbol de posibilidades
   * @return Dato miembro arbol_posibilidades
   */
  ArbolGeneral<Tablero> get_arbol_posibilidades() const {return arbol_posibilidades;}
  
  /**
   * @brief generamos el árbol de posibilidades
   * @param raiz raíz del árbol a generar
   * @param profundidad en la que se encuentra dicho nodo
   * @pre El nodo a partir del cual queremos generar el árbol, debe estar ya en el árbol
   * @return Void
   */
  void generar_arbol_posibilidades(const ArbolGeneral<Tablero>::Nodo& raiz, int profundidad); 
  
  /**
   * @brief Actualiza el árbol de posibilidades, dejando como raíz el tablero pasado y completando el árbol hasta la profundidad MAX_DEPTH
   * @param tablero actual, a partir del cual se regenera el árbol
   */
  void actualizar(const Tablero& tablero);
  
  /**
   * @brief Devuelve el mejor tablero
   * @return tablero a utilizar por el jugador automático
   */
  Tablero mejor_tablero(Tablero tablero);

  /**
   * @brief Recorre el árbol devolviendo el mejor tablero 
   * @param raiz Nodo que será la raíz del subárbol a recorrer
   * @return un pair formado por el mejor tablero (en forma de nodo) y su puntuación 
   */
  pair<ArbolGeneral<Tablero>::Nodo, int> recorrer_arbol(const ArbolGeneral<Tablero>::Nodo& raiz);
  
  /**
   * @brief Si la métrica es la 3 o la 4, esta función se encarga de devolver la 
   *        puntuación del tablero según la métrica escogida 
   * @param tablero Tablero a evaluar
   * @return Puntuación del tablero
   */
  int metrica(Tablero &tablero);
  
  /**
   * @brief Mejor métrica, intenta alinear cuatro, en caso contrario, cortar las victorias rivales; si esto tampoco es posible, se inserta aleatoriamente
   * @param tablero Tablero a evaluar
   * @return Tablero correspondiente
   **/
  Tablero metrica1(Tablero &tablero);

  /**
   * @brief Segunda métrica, corta la victoria rival. Si no fuera posible, llama a la métrica 3
   * @param tablero Tablero a evaluar
   * @return Tablero correspondiente
   **/
  Tablero metrica2(Tablero &tablero);

  /**
   * @brief Métrica que sólo verifica si se produce una victoria. En caso de no victoria introducirá una puntuación aleatoria
   * @param tablero Tablero
   * @return pair tablero y puntuación máxima
   **/
  int metrica3(Tablero &tablero);
  
  /**
   * @brief Otorga puntuaciones aleatorias entre 0 y 100
   * @param tablero en el que insertará
   * @return pair tablero y puntuación máxima
   */
  int metrica4(const Tablero &tablero);

  /**
   * @brief Muestra el recorrido en preorden del árbol de posibilidades
   * @return Void
   */  
  void mostrar_arbol_preorden() {arbol_posibilidades.recorrer_preorden();}
};

#endif
