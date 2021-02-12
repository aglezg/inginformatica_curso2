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
 * Este programa utiliza la clase DFA definida en el archivo "dfa_class.h" para:
 * 1) Leer un DFA definido en un archivo "input.dfa".
 * 2) Generar un fichero '.gra' que contenga la definición de una gramática
 *    regular equivalente.
 * 
 * Compilar con:
 * g++ -std=c++14 -g -Wall -o dfa2g dfa2g.cc dfa_class.cc grammar_class.cc
 * production_class.cc
 * 
 * Ejemplo de ejecución: 
 * > $ ./dfa2g input.dfa output.gra
 **/

#include <iostream>
#include <fstream>
#include "dfa_class.h"
#include "grammar_class.h"

using namespace std;

int main (int argc, char *argv[]) {

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    cout << "Uso: ";
    cout << "./dfa2g [input.dfa] [output.gra]" << endl;
    cout << "Pruebe './dfa2g --help' para más información." << endl;   
    return 1;
  }

  // En caso de usar como parámetro "--help"
  string help = "--help";
  if (argv[1] == help) {
    ifstream help_dfa2g;
    help_dfa2g.open("help_dfa2g.txt");

    if (!help_dfa2g.fail()) {
      while (!help_dfa2g.eof()) {
        getline (help_dfa2g, help);
        cout << help << endl;
      }
    }

    help_dfa2g.close();
    return 1;
  }

  int errorapertura = 0;

  Dfa Dfa1(argv[1], errorapertura); // Lectura del DFA
  if (errorapertura == 1) {
    cout << "Error en la apertura del archivo del DFA: ";
    cout << "revisa nombre y formato." << endl;
    return 1;
  }
  
  Grammar G1 = Dfa1.ConvertToGrammar(); // Creación de Gramática Regular

  ofstream outputgra;
  outputgra.open(argv[2]);
  if (outputgra.fail()) {
  cout << "No se pudo abrir el archivo donde escribir la gramática ";
  cout << "resultante, compruebe si ingresó un nombre correcto." << endl;
  return 1;
  }

  G1.WriteGrammar(outputgra);
  outputgra.close();
  
  return 0;
}