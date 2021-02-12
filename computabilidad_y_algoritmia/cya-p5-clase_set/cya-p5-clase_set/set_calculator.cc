/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * 
 * Asignatura: Computabilidad y Algoritmia
 * 
 * @brief  Práctica #05: La clase Set
 * @author Adrian González Galván (alu0101321219@ull.edu.es)
 * @date   03/11/2020 
 * 
 * Este archivo ".cc" utiliza la clase Set definida en
 * el archivo "set_class.h" para leer de un fichero operaciones
 * entre conjuntos (con 2 operandos como máximo) y escribir sus 
 * resultados en otro fichero.
 * Dichas operaciones se separan unas de otras a través de un salto de línea.
 * 
 * Operaciones:
 * Union = +
 * Complemento Relativo = -
 * Intersección = *
 * Complemento = ! 
 * 
 * Ejemplo de operación: {2, 6} + !{5, 7, 2}
 * 
 * Compilar con: g++ -std=c++14 -g -Wall -o set_calculator set_calculator.cc  set_class.cc
 * Ejemplo de ejecución: ./set_calculator infile.txt outfile.txt
 **/

#include <iostream>
#include <vector>
#include <fstream>
#include "set_class.h"

using namespace std;

int main (int argc, char *argv[]) {

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    cout << "ERROR: ¡FALTAN PARAMETROS!" << endl << endl;
    cout << "Ejecute de la forma:"<< endl;
    cout << "./set_calculator infile.txt outfile.txt" << endl << endl; 
    cout << "Cerrando programa..." << endl;   
    return 1;
  }

  Set A, B, C, D;

  ifstream input; // archivo donde leer
  input.open(argv[1]);

  if (input.fail()) {
    cout << "No se pudo abrir el archivo, ";
    cout << "compruebe si ingresó un nombre correcto." << endl;
    return 1;
  }

  input >> A >> B >> C >> D; // leemos los conjuntos

  ofstream output;           // archivo donde escribir
  output.open(argv[2]);

  if (output.fail()) {
    cout << "No se pudo abrir el archivo, ";
    cout << "compruebe si ingresó un nombre correcto." << endl;
    return 1;
  }

  output << "A = " << A << endl; // imprimimos los conjuntos
  output << "B = " << B << endl;
  output << "C = " << C << endl;
  output << "D = " << D << endl;

  input.close();
  output.close();

return 0;
}