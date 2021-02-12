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
 * Este programa utiliza la clase DFA definida en el archivo "dfa_class.h" para:
 * 1) Leer un DFA definido en un archivo "input.dfa".
 * 2) Leer cadenas guardadas y separadas por saltos de línea en otro
 *    archivo "input.txt".
 * 3) Determinar si esas cadenas son reconocidas por el DFA, escribiendo
 *    "Sí --" o "No -- " según el caso en un archivo de salida "output.txt".
 * 
 * Compilar con:
 * g++ -std=c++14 -g -Wall -o dfa_simulation dfa_simulation.cc  dfa_class.cc
 * 
 * Ejemplo de ejecución: 
 * > $ ./dfa_simulation input.dfa input.txt output.txt
 **/

#include <iostream>
#include <fstream>
#include "dfa_class.h"

using namespace std;

int main (int argc, char *argv[]) {

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    cout << "Modo de empleo: ";
    cout << "./dfa_simulation [input.dfa] [input.txt] [output.txt]" << endl;
    cout << "Pruebe './dfa_simulation --help' para más información" << endl;   
    return 1;
  }

  // En caso de usar como parámetro "--help"
  string help = "--help";
  if(argv[1] == help) {
    ifstream help_dfa;
    help_dfa.open("help_dfa.txt");

    if (!help_dfa.fail()) {
      while (!help_dfa.eof()) {
        getline(help_dfa, help);
        cout << help << endl;
      }
    }

    help_dfa.close();
    return 1;
  }


  int errorapertura = 0;

  DFA Dfa1(argv[1], errorapertura); // Lectura del DFA
  if (errorapertura == 1) {
    cout << "Error en la apertura del fichero del DFA: ";
    cout << "revisa nombre y formato." << endl;
    return 1;
  }

  ifstream input;                   // Archivo de lectura de cadenas
  input.open(argv[2]);
  if (input.fail()) {
    cout << "No se pudo abrir el archivo de lectura de cadenas, ";
    cout << "compruebe si ingresó un nombre correcto." << endl;
    return 1;
  }
  
  ofstream output;                  // Archivo de escritura
  output.open(argv[3]);
  if (output.fail()) {
    cout << "No se pudo abrir el archivo de escritura, ";
    cout << "compruebe si ingresó un nombre correcto." << endl;
    return 1;
  }

  // Lectura y comprobación de las cadenas
  string cadena;
  while(!input.eof()) {
    getline(input, cadena);
    if(Dfa1.BelongToLanguage(cadena))
      output << "Sí --" << endl;
    else output << "No --" << endl;
  }

  input.close();
  output.close();

  return 0;
}




