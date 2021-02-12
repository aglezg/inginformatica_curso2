/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Computabilidad y Algoritmia
 * 
 * @brief  Práctica #12: Algoritmos Voraces (Greedy)
 * @author Adrián González Galván (alu0101321219@ull.edu.es)
 * @date   12/01/2021 
 * 
 * Este programa utiliza la clse "Graph" definida en el archivo "graph.h" para:
 * 1) Leer un grafo definido en un archivo "input.gr"
 * 2) Generar el camino mínimo que resuelve el "problema del viajante" aplicando
 *    un algoritmo del tipo voraz o "greedy".
 * 
 * Compilar con:
 * > $ g++ -std=c++14 -g -Wall -o travelling_salesman travelling_salesman.cc
 *     graph.cc
 * 
 * Ejemplo de ejecución: 
 * > $ ./travelling_salesman input.gr
 **/

#include <iostream>
#include <list>
#include <fstream>
#include <stdexcept>
#include "graph.h"

using namespace std;

int ProtectedMain(int argc, char *argv[]) {

  // Comprobamos que se haya ejecutado de la forma correcta
  Usage(argv);

  // Cargamos el grafo
  bool error;
  Graph grafo(argv[1], error);
  if (error) {
    cout << "travelling_salesman: error en la apertura o lectura del fichero,";
    cout << " revise nombre y formato." << endl;
    return 1;
  }

  // Obtenemos el nodo de partida
  if (!argv[2])
    throw invalid_argument("no se ingresó un nodo inicial.");
  
  unsigned initial_node = atoi(argv[2]);
  if ((initial_node > grafo.GetNNodes()) || (initial_node == 0))
    throw invalid_argument("el nodo inicial debe pertenecer al grafo.");

  // Aplicamos el algoritmo
  list<unsigned> S;
  float coste_total = grafo.GreedyMinimumCost(initial_node, S);

  // Mostramos el resultado
  unsigned count = 0;
  if (S.empty()) cout << "S = No existe solución.\n";
  else {
    cout << "S = {";
    for (auto nodo : S)
      if (count == (S.size() - 1))
        cout << nodo << "} | " << coste_total << " kms.\n";
      else {
        cout << nodo << ", ";
        count++;
      }
  }

  return 0;
}

int main(int argc, char *argv[]) {

  try { // Mostramos los posibles errores
    return ProtectedMain(argc, argv);
  }
  catch(invalid_argument& e) {
    cerr << "travelling_salesman: " << e.what() << "\n";
    return 2;
  }
  catch(...) {
    std::cout << "travelling_salesman: error desconocido.\n";
    return 3;
  }

}