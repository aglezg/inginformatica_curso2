/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * 
 * Asignatura: Computabilidad y Algoritmia
 * 
 * @brief  Práctica #07: La clase DFA
 * @author Adrián González Galván (alu0101321219@ull.edu.es)
 * @date   17/11/2020 
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
DFA::DFA(string inputdfa, int &errorapertura) {
  
  ifstream textfile;
  textfile.open(inputdfa); 

  if (textfile.is_open()) {
    errorapertura = 0;

    // Leemos posibles comentarios
    string reader;
    do {
    getline(textfile,reader);
    }while (reader[0] ==  '/' && reader[1] == '/');

    // Leemos los símbolos del alfabeto
    numero_simbolos = stoi(reader);
    transiciones.resize(numero_simbolos + 1);

    for (int i = 1; i <= numero_simbolos; i++) {
      getline(textfile, reader);
      transiciones[i].resize(1);
      transiciones[i][0] = reader;
    }

    // Leemos los estados del DFA
    getline(textfile, reader);
    numero_estados = stoi(reader);
    for (int i = 0; i <= numero_simbolos; i++)
    transiciones[i].resize(numero_estados + 1);

    for (int i = 1; i <= numero_estados; i++) {
      getline(textfile, reader);
      transiciones[0][i] = reader;
    }

    // Leemos el estado inicial
    getline(textfile, estado_inicial);

    // Leemos los estados de aceptación
    getline(textfile, reader);
    int count = stoi (reader);

    for (int i = 1; i <= count; i++) {
      getline(textfile, reader);
      estados_aceptacion.insert(reader);
    }

    // Leemos las transiciones
    getline(textfile, reader);
    count = stoi(reader);

    int iterator = 0, fila = 0, columna = 0;
    while (iterator < count) {

      // Primer estado
      getline(textfile, reader, ' ');
      for (int i = 1; i <= numero_estados; i++)
        if (reader == transiciones[0][i])
          fila = i;

      // Simbolo
      getline(textfile, reader, ' ');
      for (int i = 1; i <= numero_simbolos; i++)
        if (reader == transiciones[i][0])
          columna = i;

      // Segundo estado
      getline(textfile, reader);
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
DFA::~DFA() {
  estados_aceptacion.clear();
  transiciones.clear();
}

// Pasado por parámetro un string (cadena)
// Determina si se trata de un símbolo reconocido
// por el DFA devolviendo un 1 y un cero en caso
// contrario.
bool
DFA::IsASymbol(const string simbolo) {
  for (int i= 1; i <= numero_simbolos; i++)
    if (simbolo == transiciones[i][0])
      return true;
  return false;
}

// Pasado por parámetro un string (cadena)
// determina si esta es aceptada por el DFA
// devolviendo un 1 en caso de que sí y un
// cero en caso contrario.
bool
DFA::BelongToLanguage(const string cadena) {
  
  string lee_simbolo;
  string estado_actual = estado_inicial;

  int fila_estado, columna_simbolo;
  
  for (unsigned i = 0; i < cadena.size(); i++) {
 
    // Leemos el símbolo i-ésimo de la cadena
    lee_simbolo = cadena[i];
    if (!IsASymbol(lee_simbolo))
      return false;

    // Localizamos el estado actual
    for (int j = 1; j <= numero_estados; j++)
      if (estado_actual == transiciones[0][j])
        fila_estado = j;
    
    // Localizamos el símbolo con el que transita
    for (int j = 1; j <= numero_simbolos; j++)
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