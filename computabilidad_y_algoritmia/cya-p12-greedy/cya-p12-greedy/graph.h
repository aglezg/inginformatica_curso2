/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Computabilidad y Algoritmia
 *
 * @brief  Práctica #12: Algoritmos Voraces (Greedy)
 * @author Adrián González Galván (alu0101321219@ull.edu.es)
 * @date   12/01/2021
 * 
 * Esta clase implementa la representación de un Grafo.
 * Los objetos de la misma se construyen a través de un fichero
 * de texto donde se ha de especificar el grafo.
 * En él se incluye el algoritmo voraz utilizado en esta práctica para
 * resolver el "problema del viajante".
 * 
 * Más información sobre el concepto de "grafo" en:
 * https://en.wikipedia.org/wiki/Graph
 * 
 * Más información sobre el "problema del viajante" en:
 * https://en.wikipedia.org/wiki/Travelling_salesman_problem
 **/

#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

// Estructura que almacena el nodo adyacente
// y su respectivo coste de un nodo en concreto.
typedef struct {
	unsigned node; // nodo
	float    cost; // coste
} ListElement;


typedef list<ListElement> v_LE; // Vector de nodo-coste

class Graph {
  
 public:
  // Constructor & Destructor
  Graph(string nombrefichero, bool &errorapertura);
  ~Graph();

  // Getter
  unsigned GetNNodes(void);

  // Algoritmo voraz
  float GreedyMinimumCost(unsigned start_node, list<unsigned>& result_list);

  // Otros métodos
  void GraphInformation();
  
  private:
    unsigned n_nodes;              // Numero de nodos
	  vector<v_LE> transitions_list; // Lista de transiciones
};

void Usage(char *argv[]);