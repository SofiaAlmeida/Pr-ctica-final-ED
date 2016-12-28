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
int jugar_partida(int filas = 4, int columnas = 4, int metrica = 1, int turno = 1) {
  //(filas, columnas, metrica, turno)
  //..lo de los comentarios con //.. es para luego buscarlos y borrarlos
  //.. ¿y si jugamos la partida dentro de conecta4?, así podríamos almacenar el tablero dentro... ¿se podría tener un único tablero que viera jugar_partida y conecta4?
  Tablero tablero(filas, columnas, turno);      //Tablero filasxcolumnas 
  Mando mando(tablero);       //Mando para controlar E/S de tablero
  char c = 1;
  //..int pos;
  int quienGana = tablero.quienGana();
  //mientras no haya ganador y no se pulse tecla de terminación
  while(c != Mando::KB_ESCAPE && quienGana == 0) {
    system("clear");
    //..if(tablero.GetTurno() == 1)
//..el jugador automático es siempre el 2 y el humano siempre el 1. Eso es lo que recibe como argumento al llamar al programa en <turno>
      //.. conecta4.actualizarJuego(columna); 
      //.. cout << tablero
    quienGana = tablero.quienGana();    // ¿hay ganador?
    if(quienGana == 0)
       c = getch();       // Capturamos la tecla pulsada.
    //..else {
       mando.actualizarJuego(c, tablero);  // actualiza tablero según comando c
    imprimeTablero(tablero, mando);     // muestra tablero y mando en pantalla
      //.. quienGana = tablero.quienGana()
      //.. if(quienGana == 0)
        //.. pos = jugadorautomatico.columna(metrica)
    //.. }

    //.. Esto está un poco al revés, porque si es el turno del jugador 1 va a actualizar lo anterior del jugador 2, actualiza la jugada anterior de este jugador. Cuando juega el jugador 1, lo que queremos actualizar es lo del jugador 2 que fue el que jugó antes
         
  }

  return tablero.quienGana();
}

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
  
  
