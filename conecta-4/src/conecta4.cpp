#include "conecta4.h"


Conecta4::actualizarJuego(char c, Tablero Tablero) {
  //TODO
}

void Conecta4::turnoAutomatico(Tablero &tablero) { // Cuando sea el turno del jugador automático llamamos a esta función para que elija dónde se ha de insertar la ficha, llamamos a colocar ficha dentro de cada métrica
  int columna;
 
  switch (metrica){

  case 1:
    columna = metrica1(tablero);
    break;
  case 2:
    columna = metrica2(tablero);
    break;
  case 3:
    columna = metrica_penultima(tablero);
    break;
  case 4:
    columna = metrica_ultima(tablero);
    break;
  default:
    cout << "Error en selección de métrica para inserción." << endl;
    //-- ¿Ponemos exit(-1); para que se detenga el programa?
  }
} 
  
void Conecta4::metrica1() {
  //TODO
}

 
void Conecta4::metrica_ultima(Tablero tablero) {
  int columna;

  do {
    columna  = rand() % tablero.GetColumnas();

  } while (!colocarFicha);

}
      
