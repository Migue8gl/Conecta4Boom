#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf = 9999999999.0, menosinf = -9999999999.0;

// Constructor
Player::Player(int jug)
{
   jugador_ = jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment &env)
{
   actual_ = env;
}

double Puntuacion(int jugador, const Environment &estado)
{
   double suma = 0;

   for (int i = 0; i < 7; i++)
      for (int j = 0; j < 7; j++)
      {
         if (estado.See_Casilla(i, j) == jugador)
         {
            if (j < 3)
               suma += j;
            else
               suma += (6 - j);
         }
      }

   return suma;
}

// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador)
{
   int ganador = estado.RevisarTablero();

   if (ganador == jugador)
      return 99999999.0; // Gana el jugador que pide la valoracion
   else if (ganador != 0)
      return -99999999.0; // Pierde el jugador que pide la valoracion
   else if (estado.Get_Casillas_Libres() == 0)
      return 0; // Hay un empate global y se ha rellenado completamente el tablero
   else
      return Puntuacion(jugador, estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)

double eval(const Environment &estado, int jugador)
{
   double cVert = 0;
   double cHoriz = 0;
   double cDiago1 = 0, cDiago2 = 0;
   double mid = 0;
   double cBomba = 0;
   double cEnem = 0;

   int otro = 1;

   if (jugador == 1)
      otro = 2;

   for (double i = 0; i < 7; i++)
   {
      for (double j = 0; j < 7; j++)
      {
         if (estado.See_Casilla(i, j) == jugador || estado.See_Casilla(i, j) == jugador + 3)
         {
            if (estado.See_Casilla(i, j + 1) == jugador || estado.See_Casilla(i, j + 1) == jugador + 3)
            {
               cHoriz += 5;
               if (estado.See_Casilla(i, j + 2) == jugador || estado.See_Casilla(i, j + 2) == jugador + 3)
                  cHoriz += 15;
            }

            if (estado.See_Casilla(i + 1, j) == jugador || estado.See_Casilla(i + 1, j) == jugador + 3)
            {
               cVert += 5;
               if (estado.See_Casilla(i + 2, j) == jugador || estado.See_Casilla(i + 2, j) == jugador + 3)
                  cVert += 15;
            }

            if (estado.See_Casilla(i + 1, j + 1) == jugador || estado.See_Casilla(i + 1, j + 1) == jugador + 3)
            {
               cDiago1 += 5;
               if (estado.See_Casilla(i + 2, j + 2) == jugador || estado.See_Casilla(i + 2, j + 2) == jugador + 3)
                  cDiago1 += 15;
            }

            if (estado.See_Casilla(i + 1, j - 1) == jugador || estado.See_Casilla(i + 1, j - 1) == jugador + 3)
            {
               cDiago2 += 5;
               if (estado.See_Casilla(i + 2, j - 2) == jugador || estado.See_Casilla(i + 2, j - 2) == jugador + 3)
                  cDiago2 += 15;
            }

            if (estado.See_Casilla(i, j) == jugador && j > 2 && j < 5)
               mid += 1;

            if (estado.See_Casilla(i, j) == jugador + 3)
               cBomba += 25;
         }
         else if (estado.See_Casilla(i, j) == otro || estado.See_Casilla(i, j) == otro + 3)
         {
            if (estado.See_Casilla(i, j + 1) == otro || estado.See_Casilla(i, j + 1) == otro + 3)
            {
               if (estado.See_Casilla(i, j + 2) == jugador)
                  cEnem += 20;
            }

            if (estado.See_Casilla(i + 1, j) == otro || estado.See_Casilla(i + 1, j) == otro + 3)
            {
               if (estado.See_Casilla(i + 2, j) == jugador)
                  cEnem += 20;
            }

            if (estado.See_Casilla(i + 1, j + 1) == otro || estado.See_Casilla(i + 1, j + 1) == otro + 3)
            {
               if (estado.See_Casilla(i + 2, j + 2) == jugador)
                  cEnem += 10;
            }

            if (estado.See_Casilla(i + 1, j - 1) == otro || estado.See_Casilla(i + 1, j - 1) == otro + 3)
            {
               if (estado.See_Casilla(i + 2, j - 2) == jugador)
                  cEnem += 10;
            }
         }
      }
      return 5 * (cVert + cHoriz) + cEnem + cBomba + (cDiago1 + cDiago2) * 0.5;
   }
}

double Valoracion(const Environment &estado, int jugador)
{
   int ganador = estado.RevisarTablero();

   if (ganador == jugador)
      return 99999999.0; // Gana el jugador que pide la valoracion
   else if (ganador != 0)
      return -99999999.0; // Pierde el jugador que pide la valoracion
   else if (estado.Get_Casillas_Libres() == 0)
      return 0; // Hay un empate global y se ha rellenado completamente el tablero
   else
   {
      int otro = 1;

      if (jugador == 1)
         otro = 2;

      double evalJug = eval(estado, jugador);
      double evalOtro = eval(estado, otro);

      return evalJug - evalOtro;
   }
}

// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j)
{
   j = 0;
   for (int i = 0; i < 8; i++)
   {
      if (aplicables[i])
      {
         opciones[j] = i;
         j++;
      }
   }
}

double podaAlphaBeta(const Environment &actual_, int jug_, int prof_act, const int &MAX_PROF, Environment::ActionType &accion, double alpha, double beta)
{
   double val;

   if (prof_act == MAX_PROF)
      return Valoracion(actual_, jug_);
      
   Environment *V = new Environment[8];
   int num_mov = actual_.GenerateAllMoves(V);

   if (prof_act < MAX_PROF && !actual_.JuegoTerminado())
   {
      if (actual_.JugadorActivo() == jug_)
      {
         for (int i = 0; i < num_mov; i++)
         {
            val = podaAlphaBeta(V[i], jug_, prof_act + 1, MAX_PROF, accion, alpha, beta);

            if (alpha < val)
            {
               alpha = val;
               if (prof_act == 0)
                  accion = static_cast<Environment::ActionType>(V[i].Last_Action(actual_.JugadorActivo()));
            }

            if (beta <= alpha)
               break;
         }
         return alpha;
      }
      else
      {
         for (int i = 0; i < num_mov; i++)
         {
            val = podaAlphaBeta(V[i], jug_, prof_act + 1, MAX_PROF, accion, alpha, beta);

            if (beta > val)
            {
               beta = val;
               //accion = static_cast<Environment::ActionType>(V[i].Last_Action(actual_.JugadorActivo()));
            }

            if (beta <= alpha)
               break;
         }
         return beta;
      }
   }
   return Valoracion(actual_, jug_);
}

// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think()
{
   const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
   const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

   Environment::ActionType accion; // acci�n que se va a devolver
   bool aplicables[8];             // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                                   // aplicables[0]==true si PUT1 es aplicable
                                   // aplicables[1]==true si PUT2 es aplicable
                                   // aplicables[2]==true si PUT3 es aplicable
                                   // aplicables[3]==true si PUT4 es aplicable
                                   // aplicables[4]==true si PUT5 es aplicable
                                   // aplicables[5]==true si PUT6 es aplicable
                                   // aplicables[6]==true si PUT7 es aplicable
                                   // aplicables[7]==true si BOOM es aplicable

   double valor;       // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
   double alpha, beta; // Cotas de la poda AlfaBeta

   int n_act; //Acciones posibles en el estado actual

   n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
   int opciones[10];

   // Muestra por la consola las acciones aplicable para el jugador activo
   //actual_.PintaTablero();
   cout << " Acciones aplicables ";
   (jugador_ == 1) ? cout << "Verde: " : cout << "Azul: ";
   for (int t = 0; t < 8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr(static_cast<Environment::ActionType>(t));
   cout << endl;

   /* //--------------------- COMENTAR Desde aqui
   cout << "\n\t";
   int n_opciones = 0;
   JuegoAleatorio(aplicables, opciones, n_opciones);

   if (n_act == 0)
   {
      (jugador_ == 1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
   }
   else if (n_act == 1)
   {
      (jugador_ == 1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " Solo se puede realizar la accion "
           << actual_.ActionStr(static_cast<Environment::ActionType>(opciones[0])) << endl;
      accion = static_cast<Environment::ActionType>(opciones[0]);
   }
   else
   { // Hay que elegir entre varias posibles acciones
      int aleatorio = rand() % n_opciones;
      cout << " -> " << actual_.ActionStr(static_cast<Environment::ActionType>(opciones[aleatorio])) << endl;
      accion = static_cast<Environment::ActionType>(opciones[aleatorio]);
   }

   //--------------------- COMENTAR Hasta aqui*/

   //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------

   // Opcion: Poda AlfaBeta
   // NOTA: La parametrizacion es solo orientativa
   valor = podaAlphaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, menosinf, masinf);
   cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

   return accion;
}
