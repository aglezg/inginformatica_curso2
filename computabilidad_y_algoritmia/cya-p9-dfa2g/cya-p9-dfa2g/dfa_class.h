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
 * Esta clase implementa la representación de un Autómata
 * Finito Determinista (DFA). En él se incluye pues el desarrollo
 * de los correspondientes métodos que permiten determinar si una
 * cadena pertenece al lenguaje que este autómata representa, asimismo
 * cuenta con un método que permite obtener la gramática regular
 * equivalente al mismo.
 * 
 * Más información sobre el concepto de "DFA" en:
 * https://en.wikipedia.org/wiki/Deterministic_finite_automaton
 **/

#pragma once

#include "grammar_class.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

typedef vector<string> v_strings;

class Dfa {

  public:  // métodos
    
     Dfa(string inputdfa, int& errorapertura);  // constructor
    ~Dfa();                                     // destructor

    bool BelongToLanguage(const string cadena);
    bool       IsASymbol(const string simbolo);
    Grammar             ConvertToGrammar(void);

  private: // atributos

    string           estado_inicial;  // estado inicial
    set <string> estados_aceptacion;  // conjunto de estados de aceptación
    vector<v_strings>  transiciones;  // matriz que almacena las transiciones
};