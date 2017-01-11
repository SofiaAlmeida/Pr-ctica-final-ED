#include "conecta4.h"

void Conecta4::generar_arbol_posibilidades(Nodo raiz, int profundidad) {
  profundidad++; // Primero aumentamos la profundidad, pues acabamos de descender a un hijo
  int columnas = raiz.etiqueta.GetColumnas();

  int i;
  bool insertado = false; //-- La forma de insertar se hace primero se inserta en el hijo izquierda y luego insertamos en los hermanos derecha, por lo tanto primero tenemos que buscar el primer hueco, si lo hay usamos insertar__hijomasizquierda(), pero para los siguientes hijos tenemos que insertar como hermanos_derecha del hijo que ya tenemos, por eso usamos esta condicional para distinguir el tipo de inserción que tenemos que hacer
  
  for ( i = 0; i < columnas || insertado == true; ++i) {
    if (raiz.etiqueta.hayHueco(i)) {	//-- Comprobar si se empieza a contar en la columa 0 o en la columna 1, si es en la 1 hay que cambiar i = 1 y la condición < por <=
     insertado = raiz.etiqueta.colocarFicha(i);
      
    }
  
  
}

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
  ArbolGeneral<Tablero> posibilidades(tablero);
  //..No sé como hacer esto usando el dato que ya tenemos...
  //..pendiente de revisión
  int pos = 0;
  int columnas = tablero.GetColumnas();
  bool gana = false;
  //..NO FUNCIONA
  for(pos = 0; pos < columnas && !gana; ++pos) {
    Tablero aux(tablero);
    aux.colocarFicha(pos);
    cout << "En la pos " << pos; //..
    if(aux.quienGana() == 2) {
      gana = true;
      cout << "gana" << endl;
      return tablero.colocarFicha(pos);
    }
    else {
      cout << "no gana" << endl;
      return metrica_ultima(tablero);
    }
  }
  //.. evitar perder...NO FUNCIONA - REVIEW
  /* bool evitar_derrota = false;

  for(pos = 0; pos < columnas && !evitar_derrota; ++pos) {
     Tablero aux(tablero);
     aux.cambiarTurno();
     aux.colocarFicha(pos);
     if(aux.quienGana() == 1) //..poner una variable
       evitar_derrota = true;
  }
  if(evitar_derrota) {
    return tablero.colocarFicha(pos);
  }
  else
  return metrica_ultima(tablero);*/
}

 
bool Conecta4::metrica_ultima(Tablero &tablero) {
  int columna;
  bool colocada = false;

  //..¿if(tablero.Lleno())? return colocada //— en ese caso directamente acabaría la partida, porque si no intentará insertar de nuevo
  do {
    columna  = rand() % tablero.GetColumnas();
    colocada = tablero.colocarFicha(columna);
  } while (!colocada);

  tablero.cambiarTurno();
  return colocada;
}
