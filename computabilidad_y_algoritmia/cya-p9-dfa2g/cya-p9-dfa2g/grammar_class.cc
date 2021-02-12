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
 * Este archivo ".cc" desarrolla los métodos de la clase Grammar
 * (definidos en el archivo "regular_grammar_class.h").
 **/

#include "grammar_class.h"

// Constructor de la clase Grammar:
// Inicializa todos los atributos menos el conjunto
// de producciones.
Grammar::Grammar(string s_arranque, set<string>
                  terminales, set<string> no_terminales) {
simbolo_arranque = s_arranque;
simbolos_terminales = terminales;
simbolos_no_terminales = no_terminales;
}

// Destructor de la clase Grammar:
// Limpia el contenido de los conjuntos
// de la misma clase.
Grammar::~Grammar() {
  simbolos_terminales.clear();
  simbolos_no_terminales.clear();
  produccion.clear();
}

// Getters
string
Grammar::GetStartSymbol(void) {
  return simbolo_arranque;
}

set<string>
Grammar::GetTerminalSymbols(void) {
  return simbolos_terminales;
}

set<string>
Grammar::GetNonTerminalSymbols(void) {
  return simbolos_no_terminales;
}

// Dada una producción por parámetro, la inserta en el
// vector de producciones de la gramática regular.
void
Grammar::InsertProduction(Production production) {
  produccion.push_back(production);
}

// Escribe los elementos de la gramática por pantalla
// (por defecto) si no se especifica otro tipo de salida.
void
Grammar::WriteGrammar(ostream& os) {

  os << simbolos_terminales.size() << endl;
  set<string>::iterator it = simbolos_terminales.begin();
  for (; it != simbolos_terminales.end(); it++)
    os << *it << endl;

  os << simbolos_no_terminales.size() << endl;
  it = simbolos_no_terminales.begin();
  for (; it != simbolos_no_terminales.end(); it++)
    os << *it << endl;

  os << simbolo_arranque << endl;

  unsigned numero_producciones = 0;
  for (unsigned i = 0; i < produccion.size(); i++)
    numero_producciones += produccion[i].GetGeneratedString().size();
  os << numero_producciones << endl;

  for (unsigned i = 0; i < produccion.size(); i++)
    produccion[i].WriteProduction(os);

}
