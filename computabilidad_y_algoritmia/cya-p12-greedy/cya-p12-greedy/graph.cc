/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Computabilidad y Algoritmia
 *
 * @brief  Práctica #12: Algoritmos Voraces (Greedy)
 * @author Adrián González Galván (alu0101321219@ull.edu.es)
 * @date   12/01/2021
 * 
 * Este archivo ".cc" desarrolla los métodos de la clase Graph
 * (definidos en el archivo "graph.h").
 **/

#include "graph.h"

// Constructor: inicializa el grafo a través de un fichero.
Graph::Graph(string nombrefichero, bool &errorapertura) {

  string reader;
  ifstream textfile;
  textfile.open(nombrefichero);

  if (textfile.is_open()) {

    errorapertura = 0;

    textfile >> (unsigned &) n_nodes >> reader;
    transitions_list.resize(n_nodes);

    unsigned i, j;
    float c;

    if ((reader == "d") && (n_nodes > 1)) {

      do {
      
        textfile >> i >> j >> c;

        if ( (i > n_nodes) || (j > n_nodes) || (i == 0) || (j == 0))
          throw invalid_argument("nodos no especificados o no válidos.");

        ListElement element;
        element.node = j-1;
        element.cost = c;
        transitions_list[i-1].push_back(element); 
      
      } while (!textfile.eof());

    }
    else if ((reader == "nd") && (n_nodes > 1)) {  
   
      do {
        
        textfile >> i >> j >> c;

        if ((i > n_nodes) || (j > n_nodes) || (i == 0) || (j == 0))
          throw invalid_argument("nodos no especificados o no válidos.");

        ListElement element;
        element.node = j-1;
        element.cost = c;
        transitions_list[i-1].push_back(element);

        element.node = i-1;
        transitions_list[j-1].push_back(element);
      
      } while (!textfile.eof());

    }
    else {
      if (!((reader == "d") || (reader == "nd")))
      errorapertura = 1;
    }

  }
  else errorapertura = 1;
  textfile.close();
}

// Destructor
Graph::~Graph() {
  for (unsigned i = 0; i < transitions_list.size(); i++)
    transitions_list[i].clear();
  transitions_list.clear();
}

// Devuelve el número de nodos
unsigned
Graph::GetNNodes(void) {
  return n_nodes;
}

// Algoritmo del tipo voraz o "greedy" que resuelve el problema del viajante.
// Devuelve el mínimo coste resultante y  escribe el camino seguido en la lista
// que se le pasa por parámetro.
// Devuelve una lista vacía y un coste de cero si no halló solución.
float
Graph::GreedyMinimumCost(unsigned start_node, list<unsigned>& result_list) {

  unsigned n_visited_nodes = 1, actual_node = start_node - 1;
  float cost = 0.0, minimum;
  vector<bool> visited(n_nodes);

  // Si solo existe un nodo la solución es instantánea
  result_list.push_back(start_node);
  if (n_nodes == 1)
    return 0.0;
  
  // Inicializamos el vector de nodos visitados
  for (unsigned i = 0; i < visited.size(); i++) visited[i] = false;
  
  // Calculamos el camino mínimo
  for (unsigned count = 1; count < n_nodes; count++) {
    
    minimum = numeric_limits<float>::infinity();
    visited[actual_node] = true;

    for (auto element : transitions_list[actual_node])
      if ((element.cost < minimum) && !visited[element.node])
        minimum = element.cost;

    for (auto element : transitions_list[actual_node])
      if ((element.cost == minimum) && !visited[element.node]) {
        actual_node = element.node;
        result_list.push_back(actual_node + 1);
        cost += minimum;
        n_visited_nodes++;
        break;
      }
    
  }

  // Añadimos la transición al nodo inicial para finalizar el camino
  for (auto element : transitions_list[actual_node])
    if (element.node == (start_node - 1)) {
      cost += element.cost;
      result_list.push_back(start_node);
      }
  
  // Comprobamos si hemos visitado todos los nodos y hemos vuelto al inicial
  if ((n_visited_nodes != n_nodes) || (start_node != result_list.back())) {
    result_list.clear(); // No hay solución
    cost = 0.0;
  }

  return cost;
}

// Muestra información del grafo en cuestión.
// Número de nodos + transiciones.
void
Graph::GraphInformation() {
  
  cout << "Información del grafo:\n";
  cout << "Número de nodos = " << n_nodes << "\n";
  
  for (unsigned i = 0; i < transitions_list.size(); i++) {
    cout << "[ " << i+1 << " ] --> ";
    if (transitions_list[i].size() == 0)
      cout << "null";
    for (auto element : transitions_list[i]) {
      cout << element.node + 1 << " : ";
      cout << element.cost << " | ";
    }
  cout << "\n\n";
  }

}

// Proporciona ayuda en caso de que el programa
// se ejecute sin parámetros o con "--help".
void
Usage(char *argv[]) {

  if (!argv[1]) {
    cout << "Uso: ./travelling_salesman [input.gr] [initial_node]" << endl;
    cout << "Pruebe './travelling_salesman --help' para más información." << endl;   
    exit(EXIT_SUCCESS);
  }

  string parameter{argv[1]};
  if (parameter == "--help") {
    ifstream help_txt;
    help_txt.open("help.txt");

    if (!help_txt.fail()) {
      while (!help_txt.eof()) {
        getline (help_txt, parameter);
        cout << parameter << endl;
      }
    }

    help_txt.close();
    exit(EXIT_SUCCESS);
  }
}