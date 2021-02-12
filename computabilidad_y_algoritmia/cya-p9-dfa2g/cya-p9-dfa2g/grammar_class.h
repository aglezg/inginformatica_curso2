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
 * Esta clase implementa la representación de una Gramática regular.
 * Usada principalmente en esta práctica para representar la gramática
 * regular que genera un DFA.
 * 
 * Más información sobre el concepto de "Gramática Regular" en:
 * https://en.wikipedia.org/wiki/Regular_grammar
 **/

#pragma once

#include "production_class.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

class Grammar {

  public:  // métodos
    
     Grammar(string s_arranque, set<string> terminales,   // constructor
              set<string> no_terminales);
    ~Grammar();                                           // destructor

    // Getters
    string             GetStartSymbol(void);
    set<string>    GetTerminalSymbols(void);
    set<string> GetNonTerminalSymbols(void);

    // Setters
    void InsertProduction(Production production);

    // Writer
    void WriteGrammar(ostream& = cout);

  private: // atributos

    string               simbolo_arranque; // simbolo de arranque
    set<string>       simbolos_terminales; // conjunto de símbolos terminales (alfabeto)
    set<string>    simbolos_no_terminales; // conjunto de símbolos no terminales
    vector<Production>         produccion; // conjunto (vector) de producciones
};