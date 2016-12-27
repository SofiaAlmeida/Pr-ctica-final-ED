#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>     // Linux/Windows users
//#include <termios.h>    // Mac OSX users

#include "ArbolGeneral.h"
#include "tablero.h"
#include "mando.h"

using namespace std;

/******************************************************************************/
/**
 * @brief Captura el caracter pulsado por teclado (sin necesidad de pulsar, a continuación, Enter).
 * @return: Caracter pulsado (char).
 */
char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

/******************************************************************************/
/**
 * @brief Imprime en pantalla el tablero completo, con el mando y el jugador.
 * @param t : Tablero que se va a imprimir.
 * @param m : Mando indicando la posición del jugador.
 */
void imprimeTablero(Tablero & t, Mando & m){
    cout << m.GetJugador() << endl;
    cout << t ;
    cout << m.GetBase() << endl;
    cout << m.GetMando() << endl;
}

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero filasxcolumnas, pidiendo por teclado los movimientos de ambos jugadores según turno.
 * @param filas Número de filas del tablero
 * @param columnas Número de columnas del tablero
 * @param metrica Métrica usada por el jugador automático
 * @param turno Turno del jugador que iniciará la partida
 * @return: Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida(int filas = 5, int columnas = 7, int metrica = 1, int turno = 1) {
  //(filas, columnas, metrica, turno)
  Tablero tablero(filas, columnas, turno);      //Tablero filasxcolumnas 
  Mando mando(tablero);       //Mando para controlar E/S de tablero
  char c = 1;
  int quienGana = tablero.quienGana();
  //mientras no haya ganador y no se pulse tecla de terminación
  while(c != Mando::KB_ESCAPE && quienGana == 0) {
    system("clear");
    mando.actualizarJuego(c, tablero);  // actualiza tablero según comando c 
    imprimeTablero(tablero, mando);     // muestra tablero y mando en pantalla
    quienGana = tablero.quienGana();    // ¿hay ganador?
    //De alguna forma habría que inicializar el jugador automático según la métrica ¿pasándoselo como parámetro al pedirle la columna?
    //se me ocurre tener un método columna que sea simplemente unos if-else comprobando el nº de métrica y llamando al método adecuado, que devolvería la posicion a insertar
    if(quienGana == 0)
      //if (turno == jugador automático) //para lo del turno podríamos decir que el jugador automático es siempre el 1 y el otro siempre el 2 y que eso sea lo que reciba como argumento al llamar al programa en <turno>
      //c = jugadorautomatico.columna()
      //else
      c = getch();       // Capturamos la tecla pulsada.    
  }

  return tablero.quienGana();
}

//metrica_ultima()
//aleatoria

//metrica_penultima()
//verificar únicamente si en alguna fila gana o como segundo caso evita perder, si no insertar de forma aleatoria

int main(int argc, char *argv[]){

  int ganador;
  
  if(argc == 1)
    ganador = jugar_partida();
  else if(argc == 2)
    ganador = jugar_partida(stoi(argv[1]));
  else if(argc == 3)
    ganador = jugar_partida(stoi(argv[1]), stoi(argv[2]));
  else if(argc == 4)
    ganador = jugar_partida(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));
  else if(argc == 5)
    ganador = jugar_partida(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]), stoi(argv[4]));
  else {
    cout << "Número de argumentos incorrecto, por favor introduzca un número adecuado" << endl;
    cout << "prompt %> conecta4 <filas_tablero> <cols_tablero> <metrica> <turno>" << endl;
    return 1;
  }

  cout << "Ha ganado el jugador " << ganador << endl;
}  
  
  
