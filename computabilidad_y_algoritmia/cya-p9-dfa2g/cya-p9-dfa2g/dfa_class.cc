/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * 
 * Asignatura: Computabilidad y Algoritmia
 * 
 * @brief  Práctica #09: Autómatas Finitos y Gramáticas Regulares
 * @author Adrián González Galván (alu0101321219@ull.edu.es)
 * @date   01/12/2020 
 * 
 * Este archivo ".cc" desarrolla los métodos de la clase DFA
 * (definidos en el archivo "dfa_class.h").
 **/

#include "dfa_class.h"

// Constructor de la clase DFA.
// Dado el nombre de un fichero por parámetro
// lee el dfa almacenado en él e inicializa los
// atributos de la clase.
// El parámetro errorapertura se igualará a 1 si
// hubo algún error con el fichero en cuestión.
Dfa::Dfa(string inputdfa, int &errorapertura) {
  
  ifstream textfile;
  textfile.open(inputdfa); 

  if (textfile.is_open()) {
    errorapertura = 0;

    // Leemos posibles comentarios
    string reader;
    do {
    getline (textfile,reader);
    } while (reader[0] ==  '/' && reader[1] == '/');

    // Leemos los símbolos del alfabeto
    transiciones.resize(stoi(reader) + 1);

    for (unsigned i = 1; i < transiciones.size(); i++) {
      getline (textfile, reader);
      transiciones[i].resize(1);
      transiciones[i][0] = reader;
    }

    // Leemos los estados del DFA
    getline (textfile, reader);
    for (unsigned i = 0; i < transiciones.size(); i++)
    transiciones[i].resize(stoi(reader) + 1);

    for (unsigned i = 1; i < transiciones[0].size(); i++) {
      getline (textfile, reader);
      transiciones[0][i] = reader;
    }

    // Leemos el estado inicial
    getline (textfile, estado_inicial);

    // Leemos los estados de aceptación
    getline (textfile, reader);
    int count = stoi (reader);

    for (int i = 1; i <= count; i++) {
      getline (textfile, reader);
      estados_aceptacion.insert(reader);
    }

    // Leemos las transiciones
    getline (textfile, reader);
    count = stoi(reader);

    int iterator = 0, fila = 0, columna = 0;
    while (iterator < count) {

      // Primer estado
      getline (textfile, reader, ' ');
      for (unsigned i = 1; i < transiciones[0].size(); i++)
        if (reader == transiciones[0][i])
          fila = i;

      // Simbolo
      getline (textfile, reader, ' ');
      for (unsigned i = 1; i < transiciones.size(); i++)
        if (reader == transiciones[i][0])
          columna = i;

      // Segundo estado
      getline (textfile, reader);
      transiciones[columna][fila] = reader;
     
      iterator++;
    }

  }
  else {
    errorapertura = 1;
  }

  textfile.close();

}

// Destructor de la clase DFA.
// Limpia el contenido de los vectores
// y conjuntos de la misma clase.
Dfa::~Dfa() {
  estados_aceptacion.clear();
  transiciones.clear();
}

// Pasado por parámetro un string (cadena)
// Determina si se trata de un símbolo reconocido
// por el DFA devolviendo un 1 y un cero en caso
// contrario.
bool
Dfa::IsASymbol(const string simbolo) {
  for (unsigned i= 1; i < transiciones.size(); i++)
    if (simbolo == transiciones[i][0])
      return true;
  return false;
}

// Pasado por parámetro un string (cadena)
// determina si esta es aceptada por el DFA
// devolviendo un 1 en caso de que sí y un
// cero en caso contrario.
bool
Dfa::BelongToLanguage(const string cadena) {
  
  string lee_simbolo;
  string estado_actual = estado_inicial;

  int fila_estado, columna_simbolo;
  
  for (unsigned i = 0; i < cadena.size(); i++) {
 
    // Leemos el símbolo i-ésimo de la cadena
    lee_simbolo = cadena[i];
    if (!IsASymbol(lee_simbolo))
      return false;

    // Localizamos el estado actual
    for (unsigned j = 1; j < transiciones[0].size(); j++)
      if(estado_actual == transiciones[0][j])
        fila_estado = j;
    
    // Localizamos el símbolo con el que transita
    for (unsigned j = 1; j < transiciones.size(); j++)
      if (lee_simbolo == transiciones[j][0])
        columna_simbolo = j;

    // Establecemos nuevo estado
    estado_actual = transiciones[columna_simbolo][fila_estado];

  }     

  // Comprobamos si ese estado es de aceptación o no
  set<string>::iterator it = estados_aceptacion.begin();
  for (; it != estados_aceptacion.end(); it ++)
    if (*it == estado_actual)
      return true;
 
  return false;
}

// Devuelve un objeto de la clase 'Grammar' equivalente
// (que reconoce el mismo lenguaje que el que reconoce el DFA).
Grammar
Dfa::ConvertToGrammar(void) {

  // Creación de gramática equivalente
  string simbolo_arranque = estado_inicial;
  set<string> Terminales, NoTerminales;

  for (unsigned i = 1; i < transiciones.size(); i++)
    Terminales.insert(transiciones[i][0]);

  for (unsigned i = 1; i < transiciones[0].size(); i++)
    NoTerminales.insert(transiciones[0][i]);

  Grammar Gramatica(simbolo_arranque, Terminales, NoTerminales);

  // Adición de producciones equivalentes a la gramática
  for (unsigned i = 1; i < transiciones[0].size(); i++) {
    string simbolo_productor = transiciones[0][i];
    set<string> cadenas_generadas;
    for (unsigned j = 1; j < transiciones.size(); j++)
      cadenas_generadas.insert(transiciones[j][0] + transiciones[j][i]);
    
    // Estado de aceptación = produce la cadena vacía (~)
    set<string>::iterator it = estados_aceptacion.begin();
    for (; it != estados_aceptacion.end(); it++)
      if (simbolo_productor == *it)
        cadenas_generadas.insert("~");

    Production produccion(simbolo_productor, cadenas_generadas);
    Gramatica.InsertProduction(produccion);
  }
  return Gramatica;
}