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
 * Esta clase implementa la representación de una producción, elemento
 * de una gramática regular.
 * 
 * Más información sobre el concepto de "Reglas de producción" en:
 * https://en.wikipedia.org/wiki/Production_(computer_science)
 **/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

class Production {

  public:  // métodos
    
     Production(string simbolo, set<string> sustitucion);  // constructor
    ~Production();                                         // destructor

    // Getters
    string           GetStartSymbol(void);
    set<string>& GetGeneratedString(void);

    // Writer
    void WriteProduction(ostream& = cout);

  private: // atributos

    string     simbolo_arranque; // Símbolo que genera la producción
    set<string> cadena_generada; // Conjunto de cadenas generadas
};