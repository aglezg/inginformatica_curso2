/********************************************************************************
* ULL - Escuela Superior de Ingeniería y Tecnología                             *
* Grado en Ingeniería Informática - Curso nº 2                                  *
*                                                                               *
* Asignatura: Computabilidad y algoritmia.                                      *
* Práctica#03: Productos capicúa.                                               *
*                                                                               *
* Autor: Adrián González Galván                                                 *
* e-mail: alu0101321219@ull.edu.es                                              *
* Fecha: 20/10/2020                                                             *
*                                                                               *
* Este programa calcula todos los números capicúas resultantes de multiplicar   *
* 2 números de n cifras/digitos cada uno. El resultado lo guarda en un fichero  *
* de texto que es pasado por parámetros de ejecución (al igual que el número n  *
* de cifras en cuestión).                                                       *
*                                                                               *
* Más información en: es.wikipedia.org/wiki/Palíndromo                          *
*                                                                               *
* Compilar con: $ g++ -std=c++14 -g -Wall -o palindrome_prod palindrome_prod.cc *
* Ejemplo de ejecución: ./palindrome_prod 2 output.txt                          *
*********************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include <math.h>
#include <cstdlib>
#include "palindrome_prod.h"

using namespace std;

int main(int argc, char *argv[]) {

  if (!argv[1]) {
    cout << "ERROR: ¡FALTAN PARAMETROS!" << endl << endl;
    cout << "Ejecute de la forma:"<< endl;
    cout << "./palindrome_prod 'num de digitos' 'archivo.txt'" << endl << endl; 
    cout << "Cerrando programa..." << endl;
    return 1;
  }

  const int kNumDigitos = atoi(argv[1]); // Numero de digitos
  if (kNumDigitos <= 0) {
    cout << "Introduzca un número entero mayor que '0'." << endl;
    cout << "Cerrando programa..." << endl;
    return 1;
  }

  ofstream archivo (argv[2]);     // Archivo donde escribir

  if (archivo.fail()) {
    cout << "No se pudo abrir el archivo, ";
    cout << "compruebe si ingresó un nombre correcto." << endl;
    return 1;
  }

  EscribeCapicuas(kNumDigitos, archivo); // Escribimos los numeros capicúas
 
  archivo.close();

  return 0;
}