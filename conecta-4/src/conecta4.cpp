#include "conecta4.hpp"

//Constructor
Conecta4::Conecta4(const Tablero& tab, int met) {
  metrica_elegida = met;
  arbol_posibilidades = ArbolGeneral<Tablero>(tab);
  generar_arbol_posibilidades(arbol_posibilidades.raiz(), 0);
}

//Generar árbol con los distintos tableros
void Conecta4::generar_arbol_posibilidades(const ArbolGeneral<Tablero>::Nodo& raiz, int profundidad) {
  profundidad++; // Primero aumentamos la profundidad, pues acabamos de descender a un hijo (en caso de ser la raíz pasamos del nivel 0 al 1)
  if (profundidad > MAX_DEPTH) // Si ya estamos a la máxima profundidad no seguimos generando hijos
    return;
  
  int columnas = arbol_posibilidades.etiqueta(raiz).GetColumnas();
  ArbolGeneral<Tablero> aux;
  Tablero hijo(arbol_posibilidades.etiqueta(raiz));
  
  
  int i;
  bool insertado = false; // Primero se inserta en el hijo izquierda y luego insertamos en los hermanos derecha. Por lo tanto, primero tenemos que buscar el primer hueco. Si lo hay, usamos insertar_hijomasizquierda(), pero para los siguientes hijosraiz tenemos que insertar como hermanos_derecha del hijo que ya tenemos, por eso usamos esta condición para distinguir el tipo de inserción que tenemos que hacer

  // Para el hijo más a la izquierda
  for (i = 0; i < columnas && !insertado; ++i) {
    if (arbol_posibilidades.etiqueta(raiz).hayHueco(i) != -1) {
      hijo.cambiarTurno();
      insertado = hijo.colocarFicha(i);
      aux.AsignaRaiz(hijo);
      arbol_posibilidades.insertar_hijomasizquierda(raiz, aux);
      generar_arbol_posibilidades(arbol_posibilidades.hijomasizquierda(raiz), profundidad);
      
    }
  }

  // Para el resto de hijos
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

//Actualiza el tablero, tomando como raíz tablero
void Conecta4::actualizar(const Tablero& tablero) {
  arbol_posibilidades.AsignaRaiz(tablero);
  generar_arbol_posibilidades(arbol_posibilidades.raiz(), 0);
}

//Tablero a utilizar por el jugador automático
Tablero Conecta4::mejor_tablero(Tablero tablero) {
  if(metrica_elegida == 1) {
    return metrica1(tablero);
  }
  else {
    if(metrica_elegida == 2)
      return metrica2(tablero);
    pair<ArbolGeneral<Tablero>::Nodo, int> p;
    p = recorrer_arbol(arbol_posibilidades.raiz());
    return arbol_posibilidades.etiqueta(p.first);
  }
}

//Recorre el árbol devolviendo el mejor tablero y su puntuación (métricas 3 y 4)
pair<ArbolGeneral<Tablero>::Nodo, int> Conecta4::recorrer_arbol(const ArbolGeneral<Tablero>::Nodo& raiz) {
  
  if(arbol_posibilidades.altura(raiz) == 0) {
    pair<ArbolGeneral<Tablero>::Nodo, int> p(raiz, metrica(arbol_posibilidades.etiqueta(raiz)));
    
    return p;
  }
  else {
    // Resto de casos
    // Para cada hijo llamo a recorrer_arbol 
    pair<ArbolGeneral<Tablero>::Nodo, int> maximo = recorrer_arbol(arbol_posibilidades.hijomasizquierda(raiz));
    maximo.second += metrica(arbol_posibilidades.etiqueta(raiz)) * arbol_posibilidades.altura(raiz);
    
    if(arbol_posibilidades.altura(raiz) != 1) {
      maximo.first = arbol_posibilidades.hijomasizquierda(raiz);
    }
    pair<ArbolGeneral<Tablero>::Nodo, int> intermedio(maximo);
    
    ArbolGeneral<Tablero>::Nodo  nodo_aux;
      
    while((arbol_posibilidades.hermanoderecha(intermedio.first)) != NULL) {
      nodo_aux = arbol_posibilidades.hermanoderecha(intermedio.first);
      
      intermedio = recorrer_arbol(nodo_aux); 
      intermedio.first =  nodo_aux;
      intermedio.second += metrica(arbol_posibilidades.etiqueta(nodo_aux)) * arbol_posibilidades.altura(nodo_aux);
      
      if(maximo.second < intermedio.second)
	maximo = intermedio;
    }
    
    return maximo;
  }
}

//Devuelve la puntuación de un tablero según la métrica elegida (3 o 4)
int Conecta4::metrica(Tablero &tablero) {

  int puntuacion;
  
  switch (metrica_elegida) {
  case 3:
    puntuacion = metrica3(tablero);
    break;
  case 4:
    puntuacion = metrica4(tablero);
    break;
  default:
    cout << "Error en selección de métrica para inserción." << endl;
    exit(-1);
  }

  return puntuacion;
} 

Tablero Conecta4::metrica1(Tablero &tablero) {
  int cols = tablero.GetColumnas();

  //Comprobamos si podemos ganar
  for(int i = 0; i < cols; ++i) {
    Tablero aux(tablero);
    if(aux.colocarFicha(i)) {
      if(aux.quienGana() == 2) {
	tablero.colocarFicha(i);
	return tablero;
      }
    }
  }

  //Cortamos jugadas ganadoras
  for(int i = 0; i < cols; ++i) {
    Tablero aux(tablero);
    aux.cambiarTurno();
    if(aux.colocarFicha(i)) {
      if(aux.quienGana() == 1) {
	tablero.colocarFicha(i);
	return tablero;
      }
    }
  }

  //Insertamos aleatoriamente
  bool insertada = false;
  do {
    int pos = rand() % cols;
    if(tablero.colocarFicha(pos))
      return tablero;
  } while(!insertada);
}

Tablero Conecta4::metrica2(Tablero &tablero) {
  int cols = tablero.GetColumnas();

  //Cortamos victorias del contrario
  for(int i = 0; i < cols; ++i) {
    Tablero aux(tablero);
    aux.cambiarTurno();
    if(aux.colocarFicha(i)) {
      if(aux.quienGana() == 1) {
	tablero.colocarFicha(i);
	return tablero;
      }
    }
  }

  //Insertamos aleatoriamente
  bool insertada = false;
  do {
    int pos = rand() % cols;
    if(tablero.colocarFicha(pos))
      return tablero;
  } while(!insertada);
}

int Conecta4::metrica3(Tablero &tablero) { 
  if (tablero.quienGana() == 0)
    return metrica4(tablero);

  if (tablero.quienGana() == 2)
    return 1000;

  else
    return -1500;
}

int Conecta4::metrica4(const Tablero& tablero) { 
  int puntuacion = rand() % 100;
  return puntuacion;
}
