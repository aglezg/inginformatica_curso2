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
 * Este archivo ".cc" desarrolla los métodos de la clase Production
 * (definidos en el archivo "production_class.h").
 **/

#include "production_class.h"

// Constructor de la clase Production:
// Inicializa los atributos de la clase.
Production::Production(string simbolo, set<string> sustitucion) {
  simbolo_arranque = simbolo;
  cadena_generada = sustitucion;
}
    
// Destructor de la clase Production:
// Limpia los conjuntos que definen la clase.
Production::~Production() {
  cadena_generada.clear();
}

// Getters
string
Production::GetStartSymbol(void) {
  return simbolo_arranque;
}

set<string>& 
Production::GetGeneratedString(void) {
  return cadena_generada;
}

// Escribe los elementos de la producción por pantalla
// (por defecto) si no se especifica otro tipo de salida.
void
Production::WriteProduction(ostream& os) {
  set<string>::iterator it = GetGeneratedString().begin();
  for (; it != GetGeneratedString().end(); it++)
    os << GetStartSymbol() << " -> " << *it << endl;
}