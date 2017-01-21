#include "conecta4.h"

Conecta4::Conecta4(const Tablero& tab, int met) {
  metrica_elegida = met;
  arbol_posibilidades = ArbolGeneral<Tablero>(tab);
  generar_arbol_posibilidades(arbol_posibilidades.raiz(), 0);
}

void Conecta4::generar_arbol_posibilidades(const ArbolGeneral<Tablero>::Nodo& raiz, int profundidad) {
  profundidad++; //-- Primero aumentamos la profundidad, pues acabamos de descender a un hijo (en caso de ser la raíz pasamos del nivel 0 al 1)
  if (profundidad > MAX_DEPTH) //-- Si ya estamos a la máxima profundidad no seguimos generando hijos
    return;
  
  int columnas = arbol_posibilidades.etiqueta(raiz).GetColumnas();
  //ArbolGeneral<Tablero>::Nodo hijo(raiz), hermano;  //-- No queremos perder el nodo hijo para poder insertar a su derecha
  ArbolGeneral<Tablero> aux;
  Tablero hijo(arbol_posibilidades.etiqueta(raiz));
  
  
  int i;
  bool insertado = false; //-- La forma de insertar se hace primero se inserta en el hijo izquierda y luego insertamos en los hermanos derecha, por lo tanto primero tenemos que buscar el primer hueco, si lo hay usamos insertar__hijomasizquierda(), pero para los siguientes hijosraiz tenemos que insertar como hermanos_derecha del hijo que ya tenemos, por eso usamos esta condicional para distinguir el tipo de inserción que tenemos que hacer
  
  for (i = 0; i < columnas && !insertado; ++i) {
    if (arbol_posibilidades.etiqueta(raiz).hayHueco(i) != -1) {
      hijo.cambiarTurno();
      insertado = hijo.colocarFicha(i);
      aux.AsignaRaiz(hijo);
      arbol_posibilidades.insertar_hijomasizquierda(raiz, aux);
      generar_arbol_posibilidades(arbol_posibilidades.hijomasizquierda(raiz), profundidad);
      
    }
  }

  //-- Para el resto de hijos
  ArbolGeneral<Tablero>::Nodo donde_insertar = arbol_posibilidades.hijomasizquierda(raiz);
  
  while (i < columnas) {
    if (arbol_posibilidades.etiqueta(raiz).hayHueco(i) != -1) {
      Tablero hermano(arbol_posibilidades.etiqueta(raiz)); 
      hermano.cambiarTurno();
      hermano.colocarFicha(i);
      aux.AsignaRaiz(hermano);
      arbol_posibilidades.insertar_hermanoderecha(donde_insertar, aux);
      donde_insertar = arbol_posibilidades.hermanoderecha(donde_insertar);
      generar_arbol_posibilidades(donde_insertar, profundidad);
    }
    i++;
  }
  return;
}

pair<ArbolGeneral<Tablero>::Nodo, int> Conecta4::recorrer_arbol(const ArbolGeneral<Tablero>::Nodo& raiz) {
  if(arbol_posibilidades.altura(raiz) == 0) {
    cout << "Altura == 0" << endl;
    pair<ArbolGeneral<Tablero>::Nodo, int> p(raiz, metrica(arbol_posibilidades.etiqueta(raiz)));
    
    return p;
  }
  else {
    //..Resto de casos
    //..Para cada hijo llamo a recorrer_arbol
    pair<ArbolGeneral<Tablero>::Nodo, int> maximo = recorrer_arbol(arbol_posibilidades.hijomasizquierda(raiz));
    //cout << "maximo " << arbol_posibilidades.etiqueta(maximo.first) << maximo.second << endl;
    if(arbol_posibilidades.altura(raiz) != 1) {
      maximo.first = arbol_posibilidades.hijomasizquierda(raiz);
    }
    pair<ArbolGeneral<Tablero>::Nodo, int> intermedio(maximo);
    
    cout << "Altura = " << arbol_posibilidades.altura(raiz) << ", hermanoderecha(intermedio.first)" << endl;
    cout << arbol_posibilidades.etiqueta(arbol_posibilidades.hermanoderecha(intermedio.first));
    ArbolGeneral<Tablero>::Nodo  nodo_aux;
      
    while((arbol_posibilidades.hermanoderecha(intermedio.first)) != NULL) {
      nodo_aux = arbol_posibilidades.hermanoderecha(intermedio.first);
      
      intermedio = recorrer_arbol(nodo_aux);
      intermedio.first =  nodo_aux;
      
      if(maximo.second < intermedio.second)
	maximo = intermedio;
    }
    cout << "Hermano derecha de: " << arbol_posibilidades.etiqueta(nodo_aux) << "NULL" << endl;
    
    return maximo;
  }
    
}

bool Conecta4::turnoAutomatico(Tablero &tablero) {
  //..Llamar a recorrer_arbol y quedarse con el tablero correspondiente
  
  // Cuando sea el turno del jugador automático llamamos a esta función para que elija dónde se ha de insertar la ficha, llamamos a colocar ficha dentro de cada métrica
  bool insertada = false;
  
  switch (metrica_elegida) {

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

void Conecta4::actualizar(const Tablero& tablero) {
  arbol_posibilidades.AsignaRaiz(tablero);
  generar_arbol_posibilidades(arbol_posibilidades.raiz(), 0);
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

int Conecta4::metrica(const Tablero& tablero) {
  cout << tablero;
  int puntuacion = rand() % 100;
  cout << "Puntuación: " << puntuacion << endl;
  return puntuacion;
}
