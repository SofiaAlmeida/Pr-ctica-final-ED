#ifndef __CONECTA4_H__
#define __CONECTA4_H__

#include "tablero.h"
#include "ArbolGeneral.h"
#include <cstdlib>		//--rand()


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
  const int MAX_DEPTH; //--Número de niveles a comprobar
  
 public:
  Conecta4(filas, columnas, metrica, turno);

  //..int columna();
  //..if metrica == 1
  //..metrica1();
  //.. ...

  //.. actualizarJuego(c, tablero)
  //..intentar colocar ficha
  //..mirar actualizarJuego de mando.cpp

  //--turnoAutomatico()
  //--cuando sea el turno del jugador automático operará según la métrica insertada
  //..metrica1
  //..si empieza, poner ficha en el centro
  //.. Cortar las jugadas rivales cuando ponga 2 o 3 fichas en línea
  //..intentar conseguir 4 en línea

  //..metrica2
  //..insertar piezas de manera colindante

  
//..metrica_ultima()
//..aleatoria

//..metrica_penultima()
//..verificar únicamente si en alguna fila gana o como segundo caso evita perder, si no insertar de forma aleatoria

};

#endif
