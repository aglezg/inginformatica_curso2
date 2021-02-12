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
* Este archivo ".h" declara y desarrolla las funciones utilizadas en            *
* "palindrome_prod.cc".                                                         *
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

// Dado un número entero pasado por parámetro, devuelve
// este mismo dado la vuelta (invertido)
int InvertirNumero(int numero){
  int resto = 0, numero_inv = 0;

  while (numero > 0){
    resto = numero % 10;
    numero /= 10;
    numero_inv = numero_inv * 10 + resto;
  }

  return numero_inv;
}

// Función que devuelve '1' si el número pasado por
// parámetro resulta ser capicúa. De lo contrario
// devuelve un '0'.
bool EsCapicua(int numero) {
  if (numero == InvertirNumero(numero)) return 1;
  else return 0;
}

// Pasados por parámetro un número de cifras/digitos y
// un archivo de texto, esta función escribe en ese archivo
// todos los números capicúas resultantes de multiplicar 2
// números del número de cifras especificado cada uno.
void EscribeCapicuas(int num_cifras, ofstream& archivo) {
  for (int i = pow(10,num_cifras-1); i <= (pow(10,num_cifras) - 1); i++)
    for (int j = i; j <= (pow(10,num_cifras) - 1); j++)
      if (EsCapicua(i*j))
        archivo << i << " x " << j << " = " << i * j << endl;
}