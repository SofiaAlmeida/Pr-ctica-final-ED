#include "conecta4.h"

bool Conecta4::turnoAutomatico(Tablero &tablero) { // Cuando sea el turno del jugador automático llamamos a esta función para que elija dónde se ha de insertar la ficha, llamamos a colocar ficha dentro de cada métrica
  bool insertada = false;
  
  switch (metrica) {

  case 1:
    insertada = metrica1(tablero);
    break;
  case 2:
    insertada = metrica2(tablero);
    break;
  case 3:
    insertada = metrica_penultima(tablero);
    break;
  case 4:
    insertada = metrica_ultima(tablero);
    break;
  default:
    cout << "Error en selección de métrica para inserción." << endl;
    exit(-1);
    //..return insertada
  }

  return insertada;
} 
  
bool Conecta4::metrica1(Tablero &tablero) {
  //TODO
}

bool Conecta4::metrica2(Tablero &tablero) {
  //TODO
}

bool Conecta4::metrica_penultima(Tablero &tablero) {
  //TODO
}

 
bool Conecta4::metrica_ultima(Tablero &tablero) {
  int columna;
  bool colocada = false;

  //..¿if(tablero.Lleno())? return colocada //-- en ese caso directamente acabaría la partida, porque si no intentará insertar de nuevo
  do {
    columna  = rand() % tablero.GetColumnas();
    colocada = tablero.colocarFicha(columna);
  } while (!colocada);

     tablero.cambiarTurno();
  return colocada;
}
      
