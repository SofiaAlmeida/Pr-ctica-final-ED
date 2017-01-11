#ifndef __CONECTA4_H__
#define __CONECTA4_H__

#include "tablero.h"
#include "ArbolGeneral.h"
#include <cstdlib>		//rand()


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
  int metrica;
  const int MAX_DEPTH = 5; //Número de niveles a comprobar
  //..puse cualquier valor para poder compilar, ya pensaremos cual queremos poner
  
 public:
  /**
   * @brief Constructor
   * @param tab tablero inicial
   * @param met metrica a utilizar durante la partida
   */
 Conecta4(Tablero tab, int met) : metrica(met) {
    arbol_posibilidades = ArbolGeneral<Tablero>(tab);
    generar_arbol_posibilidades(arbol_posibilidades.raiz(), 0) //..Raiz devuelve un const y nosotros lo estamos modificando !!
  }

  //-- Tal vez debamos pasar un segundo parámetro que sirva para saber cual es la profundidad en la que se encuentra (lo pongo por si podemos ver que funcione así)

  /**
   * @brief generamos el árbol de posibilidades
   * @param raiz raíz del árbol a generar
   * @param profundidad en la que se encuentra dicho nodo
   * @return árbol 
   */
  void generar_arbol_posibilidades(ArbolGeneral<Tablero>::Nodo& raiz, int profundidad); 
  
  
  /**
   * @brief Cuando sea el turno del jugador automático operará según la métrica insertada. 
   * En caso de ser posible insertar una ficha en la posición indicada por la métrica, modifica el tablero
   * @param tablero en el que insertará una ficha
   * @return true si se pudo insertar
   */
  bool turnoAutomatico(Tablero &tablero);
  
  /**
   * @brief Mejor métrica, en caso de empezar colocará en el centro y procurará tomar las decisiones más favorables a la par que cortar las victorias rivales
   * @param tablero Tablero dónde insertará
   * @return true si ha insertado correctamente, false en caso contrario
   **/
  bool metrica1(Tablero &tablero);

  /**
   * @brief Segunda métrica, intenta alinear el mayor número de fichas posibles
   * @param tablero Tablero donde se insertará
   * @return true si ha insertado correctamente, false en caso contrario
   **/
  bool metrica2(Tablero &tablero);

  /**
   * @brief Métrica que sólo verifica el siguiente nivel y corta la jugada rival en caso de posible derrota. Si no se decanta insertará aleatoriamente
   * @param tablero Tablero
   **/
  bool metrica_penultima(Tablero &tablero);
  
  /**
   * @brief inserta en una posición aleatoria y cambia el turno
   * @param tablero en el que insertará
   * @return true si ha podido insertar, false en caso contrario
   */
  bool metrica_ultima(Tablero &tablero);
};

#endif
