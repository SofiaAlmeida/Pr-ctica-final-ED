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
 * tablero inicial
 */
class Conecta4 {
 private:
  ArbolGeneral<Tablero> arbol_posibilidades;
  int metrica_elegida;
  const int MAX_DEPTH = 3; //Número de niveles a comprobar
 
 public:
  /**
   * @brief Constructor
   * @param tab tablero inicial
   * @param met metrica a utilizar durante la partida
   */
  Conecta4(const Tablero& tab, int met);
  

  /**
   * @brief generamos el árbol de posibilidades
   * @param raiz raíz del árbol a generar
   * @param profundidad en la que se encuentra dicho nodo
   * @pre El nodo a partir del cual queremos generar el árbol, debe estar ya en el árbol
   * @return árbol 
   */
  void generar_arbol_posibilidades(const ArbolGeneral<Tablero>::Nodo& raiz, int profundidad); 
  
  
  /**
   * @brief Cuando sea el turno del jugador automático operará según la métrica insertada. 
   * @param tablero a evaluar
   * @return puntuación del respectivo tablero
   */
  int metrica(Tablero &tablero);

  ArbolGeneral<Tablero> get_arbol_posibilidades() const {return arbol_posibilidades;}

  /**
   * @brief Muestra el recorrido en preorden del árbol de posibilidades
   * @return Void
   */  
  void mostrar_arbol_preorden() {arbol_posibilidades.recorrer_preorden();}

  /**
   * @brief actualiza el árbol de posibilidades, dejando como raíz el tablero pasado y completando el árbol hasta la profundidad MAX_DEPTH   * @param tablero actual, a partir del cual se regenera el árbol (aprovechando lo generado anteriormente
   */
  void actualizar(const Tablero& tablero);

  /**
   * @brief recorre el árbol devolviendo el mejor tablero 
   * @param Nodo que será la raíz del subárbol a recorrer
   * @return un pair formado por el mejor tablero y su puntuación 
   */
  pair<ArbolGeneral<Tablero>::Nodo, int> recorrer_arbol(const ArbolGeneral<Tablero>::Nodo& raiz);
  
  /**
   * @brief Mejor métrica, en caso de empezar colocará en el centro y procurará tomar las decisiones más favorables a la par que cortar las victorias rivales
   * @param tablero Tablero a evaluar
   * @return Puntuación correspondiente
   **/
  int metrica1(const Tablero &tablero);

  /**
   * @brief Segunda métrica, intenta alinear el mayor número de fichas posibles
   * @param tablero Tablero a evaluar
   * @return Puntuación correspondiente
   **/
  int metrica2(const Tablero &tablero);

  /**
   * @brief Métrica que sólo verifica si se produce una victoria para asignar una máxima puntuación. En caso de empate introducirá la primera jugada con la máxima puntuación obtenida
   * @param tablero Tablero
   * @return pair tablero y puntuación máxima
   **/
  int metrica_penultima(Tablero &tablero);
  
  /**
   * @brief Otorga puntuaciones aleatorias para insertar en la máxima
   * @param tablero en el que insertará
   * @return pair tablero y puntuación máxima
   */
  int metrica_ultima(const Tablero &tablero);

  
};

#endif
