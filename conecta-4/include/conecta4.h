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
   * @param met metrica a utilizar durante la partida
   */
 Conecta4(int met) : metrica(met) {}

  
  //.. actualizarJuego(c, tablero)
  //..intentar colocar ficha
  //..mirar actualizarJuego de mando.cpp


  /**
   * @brief Cuando sea el turno del jugador automático operará según la métrica insertada
   * @param tablero en el que insertará una ficha
   * @return Void
   */
  void turnoAutomatico(Tablero &tablero);
  
  //--
  //..metrica1
  //..si empieza, poner ficha en el centro
  //.. Cortar las jugadas rivales cuando ponga 2 o 3 fichas en línea
  //..intentar conseguir 4 en línea

  //..metrica2
  //..insertar piezas de manera colindante

//..metrica_penultima()
//..verificar únicamente si en alguna fila gana o como segundo caso evita perder, si no insertar de forma aleatoria

  /**
   * @brief inserta en una posición aleatoria y cambia el turno
   * @param tablero en el que insertará
   * @return true si ha podido insertar, false en caso contrario
   */
  bool metrica_ultima(Tablero &tablero);
};

#endif
