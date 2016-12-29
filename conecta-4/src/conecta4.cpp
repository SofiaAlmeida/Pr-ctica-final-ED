#include "conecta4.h"


Conecta4::actualizarJuego(char c, Tablero Tablero) {
  //--TODO
}

//.. revisar tipo de esta función según cómo la vayamos a utilizar
void Conecta4::turnoAutomatico(Tablero &tablero) { // Cuando sea el turno del jugador automático llamamos a esta función para que elija dónde se ha de insertar la ficha, llamamos a colocar ficha dentro de cada métrica
 
  switch (metrica) {

  case 1:
    metrica1(tablero);
    break;
  case 2:
    metrica2(tablero);
    break;
  case 3:
    metrica_penultima(tablero);
    break;
  case 4:
    metrica_ultima(tablero);
    break;
  default:
    cout << "Error en selección de métrica para inserción." << endl;
    exit(-1); 
  }
} 
  
int Conecta4::metrica1() {
  //TODO
}

 
bool Conecta4::metrica_ultima(Tablero &tablero) {
  int columna;
  bool colocada = false;

  //..¿if(tablero.Lleno())? return colocada
  do {
    columna  = rand() % tablero.GetColumnas();
    colocada = tablero.colocarFicha(columna);
  } while (!colocada);

     tablero.cambiarTurno();
  return colocada;
}
      
