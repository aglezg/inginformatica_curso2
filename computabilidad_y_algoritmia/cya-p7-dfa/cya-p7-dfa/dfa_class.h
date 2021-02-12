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
 * Esta clase implementa la representación de un Autómata
 * Finito Determinista (DFA). En él se incluye pues el desarrollo
 * de los correspondientes métodos que permiten determinar si una
 * cadena pertenece al lenguaje que este autómata representa.
 * 
 * Más información sobre el concepto de "DFA" en:
 * https://en.wikipedia.org/wiki/Deterministic_finite_automaton
 **/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

typedef vector<string> v_strings;

class DFA {

  public:  // métodos
    
     DFA(string inputdfa, int& errorapertura);  // constructor
    ~DFA();                                     // destructor

    bool BelongToLanguage(const string cadena);
    bool IsASymbol(const string simbolo);

  private: // atributos

    int              numero_estados;
    int             numero_simbolos;

    string           estado_inicial;
    set <string> estados_aceptacion;
    vector<v_strings>  transiciones;  // matriz que almacena las transiciones
};