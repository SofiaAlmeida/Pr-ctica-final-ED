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

const int t_humano = 1;
const int t_automatico = 2;

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
void imprimeTablero(Tablero & t, Mando & m) {
    cout << m.GetJugador() << endl;
    cout << t ;
    cout << m.GetBase() << endl;
    cout << m.GetMando() << endl;
}

//..¿esto funciona?
void imprimeTablero(Tablero &t) {
    cout << m.GetJugador() << endl;
    cout << t ;
}

//..Dejo por aquí la función original jugar_partida, jugar_partida actual está destinado a jugar con un jugador automático
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero 5x7, pidiendo por teclado los movimientos de ambos jugadores según turno.
 * @return : Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida_humanos() {

  Tablero tablero(5, 7);      //Tablero 5x7
  Mando mando(tablero);       //Mando para controlar E/S de tablero
  char c = 1;
  int quienGana = tablero.quienGana();
  //mientras no haya ganador y no se pulse tecla de terminación
  while(c != Mando::KB_ESCAPE && quienGana == 0) {
    system("clear");
    mando.actualizarJuego(c, tablero);  // actualiza tablero según comando c 
    imprimeTablero(tablero, mando);     // muestra tablero y mando en pantalla
    quienGana = tablero.quienGana();    // hay ganador?
    if(quienGana==0) c = getch();       // Capturamos la tecla pulsada.    
  }

  return tablero.quienGana();
}

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero filasxcolumnas, pidiendo por teclado los movimientos de un jugador y el otro automático
 * @param filas Número de filas del tablero
 * @param columnas Número de columnas del tablero
 * @param metrica Métrica usada por el jugador automático
 * @param turno Turno del jugador que iniciará la partida
 * @return: Identificador (int) del jugador que gana la partida (1 o 2)
 * 1: jugador humano
 * 2: jugador automático
 */
//..PROBAR
int jugar_partida(int filas = 4, int columnas = 4, int metrica = 1, int turno = 1) {
  //(filas, columnas, metrica, turno)
  
  Tablero tablero(filas, columnas, turno);      //Tablero filasxcolumnas 
  int quienGana = tablero.quienGana();
  char c = 1;
  Conecta4 j_auto(metrica);

  //Mientras no haya ganador y no se pulse la tecla de terminación
  while(c != Mando::KB_ESCAPE && quienGana = 0) {
    if(turno == t_humano) {
      imprimeTablero(tablero, mando); //Muestra tablero y mando en pantalla
      c = getch(); //Capturamos la tecla pulsada
      system("clear");
      mando.actualizarJuego(c, tablero);
    }
    else {
      imprimeTablero(tablero);
      //.. si vemos que no tarda nada sleep(1);
      j_auto.turnoAutomarico(tablero);
      imprimeTablero(tablero);
    }
    quienGana = tablero.quienGana();
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
  
  
