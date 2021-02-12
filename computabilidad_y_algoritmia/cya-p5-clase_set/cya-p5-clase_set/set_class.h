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
 * Este archivo ".h" define la clase Set usada en la práctica.
 * Para ver el desarrollo de las funciones dirígase al archivo
 * "set_class.cc".
 **/

#pragma once

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// Representa conjuntos de números naturales enteros positivos.
// Ejemplos:
// Set A(8), B(100), C;
// son conjuntos con 8, 100 y 64 elementos respectivamente.
// Algunas operaciones:
// A.SetElement(9) | B.RemoveElement(8) | C = A + B;
class Set { 

  public: // Métodos

    // Constructor
    Set(); 
    Set(const int);
  
    // Destructor
    ~Set();

    // Getters
    int GetSize();
    int GetNElements();
    vector<unsigned long> GetSet();

    // Setters
    void SetElement(unsigned int);

    // Testers
    bool IsEmpty();
    bool BelongToSet(unsigned int);

    // Operaciones entre Set's
    Set Union(Set&);
    Set RelativeComplement(Set&);
    Set Intersection(Set&);
    Set Complement();

    // Otras operaciones
    void ResizeSet(const int);
    void RemoveElement(unsigned int);
    void CleanElements();

    // Sobrecarga de operadores
    bool operator==(Set&);
    Set& operator=(Set);

    // E/S
    void write(ostream& os = cout);
    void read(istream& is = cin);

  private: // Atributos

    int size;                      // número de elementos máximo del conjunto 
    int n_elements;                 // número actual de elementos del conjunto
    vector<unsigned long> conjunto; // vector que almacena el conjunto
};

// Operadores sobrecargados de operaciones entre conjuntos
Set operator+(Set& A, Set& B);
Set operator-(Set& A, Set& B);
Set operator*(Set& A, Set& B);
Set operator!(Set& A);

// Operadores sobrecargados de entrada/salida
ostream& operator<<(ostream& os, Set& A);
istream& operator>>(istream& is, Set& A);