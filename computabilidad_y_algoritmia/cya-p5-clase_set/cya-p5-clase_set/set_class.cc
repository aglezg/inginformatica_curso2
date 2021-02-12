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
 * Este archivo ".cc" define los métodos de la clase Set
 * (desarrollados en el archivo "set_class.h").
 * 
 * Esta clase implementa la representación de conjuntos
 * de números naturales (enteros positivos). Con las
 * correspondientes operaciones de unión, interesección,
 * complemento relativo y complemento de conjuntos.
 * 
 * Más información en: en.wikipedia.org/wiki/Set_(mathematics)
 **/

#include "set_class.h"

// Constructor por defecto de la clase Set.
// Establece la dimensión del conjunto en 64,
// su número de elementos en '0' y usa
// incialmente solo un long.
Set::Set() {
  size = 8 * sizeof(long);
  n_elements = 0;
  conjunto.resize(1);
}


// Constructor de la clase Set.
// A diferencia del constructor por defecto
// este establece la dimensión del conjunto
// según el parámetro proporcionado.
Set::Set(const int new_size) {
  assert(new_size > 0);  
  size = new_size;
  n_elements = 0;
  conjunto.resize(1);
}


// Destructor de la clase Set.
// Elimina todos los elementos del conjunto.
Set::~Set(){
  CleanElements();
  conjunto.clear();
}


/* Getters */
int
Set::GetSize() {
  return size;
}



vector<unsigned long>
Set::GetSet() {
  return conjunto;
}



int
Set::GetNElements() {
  return n_elements;
}


/* Setters */
// Dado un número entero positivo pasado por 
// parámetro (un elemento), lo introduce en el 
// conjunto si es que no se excede el número
// máximo de elementos del mismo.
void
Set::SetElement(unsigned int int_element) {
  assert(int_element > 0);
  assert(GetNElements() < GetSize());

  unsigned long element = 1;
  element <<= (int_element-1);

  if(!BelongToSet(int_element)) {
  
    if ((int_element % (8 * sizeof(long))) == 0) {
      if(GetSet().size() < (int_element / (8 * sizeof(long))))
        conjunto.resize(int_element / (8 * sizeof(long)));
      conjunto[(int_element / (8 * sizeof(long))) - 1] |= element;
    }
    else {
      if(GetSet().size() < (int_element / (8 * sizeof(long)) + 1))
        conjunto.resize((int_element / (8 * sizeof(long))) + 1);
      conjunto[(int_element / (8 * sizeof(long)))] |= element;
    }
    n_elements++;
  }
}


/* Otras operaciones */
// Redimensiona el tamaño máximo del conjunto.
// Esto implica que el número de elementos del
// mismo no puede ser mayor que el nuevo tamaño.
void
Set::ResizeSet(const int new_size) {
  assert(new_size >= n_elements);
  size = new_size;
}


// Dado un número entero positivo pasado por 
// parámetro (un elemento), lo elimina del 
// conjunto si es que pertenece al mismo.
void
Set::RemoveElement(unsigned int int_element) {
  unsigned long element = 1;
  element <<= (int_element-1);

  if(BelongToSet(int_element)) {

    if (int_element % (8 * sizeof(long)) == 0)
      conjunto[(int_element / (8 * sizeof(long))) - 1] ^= element;
    else
      conjunto[(int_element / (8 * sizeof(long)))] ^= element;

  n_elements--;
}
}


// Elimina todos los elementos del conjunto
// si es que este no está vacío.
void
Set::CleanElements() {
  if(!IsEmpty())
    for(unsigned int i = 0; i < GetSet().size(); i++)
      conjunto[i] &= 0;
  n_elements = 0;
}


/* Testers */
// Determina si un conjunto está vacío (retornando
// 1) o no (retornando un 0).
bool
Set::IsEmpty() {
  if(GetNElements() == 0) return true;
  else return false;
}


// Dado un número entero positivo pasado por 
// parámetro (un elemento), determina si este
// pertenece al conjunto (retornando un 1) o
// no (retornando un 0). 
bool
Set::BelongToSet(unsigned int int_element) {
  unsigned long element = 1;
  element <<= (int_element-1);

  if ((int_element % (8 * sizeof(long))) == 0) {
    if((conjunto[(int_element / (8 * sizeof(long))) - 1] & element) == 0)
      return false;
    else return true;    
  }
  else {
    if((conjunto[(int_element / (8 * sizeof(long)))] & element) == 0)
      return false;
    else return true;
  }
}


/* Operaciones entre Set's */
// Devuelve un conjunto resultante de hacer la operación
// de la unión entre el conjunto invocante y el pasado
// por parámetro.
Set
Set::Union(Set& A) {
  unsigned int i = 1;
  unsigned int j = 0;
  Set result(1);

  if(GetSet().size() >= A.GetSet().size()) {
    while(i <= (GetSet().size() * 8 * sizeof(long))) {
      // Elementos que pertenezcan al primer o al segundo conjunto
      if(BelongToSet(i) || A.BelongToSet(i)) {
        result.ResizeSet(++j);
        result.SetElement(i);
      }
      i++;
    }
  }
  else {
    while(i <= (A.GetSet().size() * 8 * sizeof(long))) {
      if(BelongToSet(i) || A.BelongToSet(i)) {
        result.ResizeSet(++j);      
        result.SetElement(i);
      }
      i++;
    }
  }
  return result;
}



// Devuelve un conjunto resultante de hacer la operación
// del complemento relativo entre el conjunto invocante 
// y el pasado por parámetro.
Set
Set::RelativeComplement(Set& A) {
  unsigned int i = 1;
  unsigned int j = 0;
  Set result(1);

  while(i <= (GetSet().size() * 8 * sizeof(long))) {
    // Elementos que pertenezcan al primer conjunto
    // y no pertenezcan al segundo.
    if(BelongToSet(i) && !A.BelongToSet(i)) {
      result.ResizeSet(++j);
      result.SetElement(i);
    }
    i++;
  }
  return result;
}



// Devuelve un conjunto resultante de hacer la operación
// de la intersección entre el conjunto invocante y el 
// pasado por parámetro.
Set
Set::Intersection(Set& A) {
  unsigned int i = 1;
  unsigned int j = 0;
  Set result(1);

  while(i <= (GetSet().size() * 8 * sizeof(long))) {   
    // Elementos que pertenezcan a ambos conjuntos
    if(BelongToSet(i) && A.BelongToSet(i)) {
      result.ResizeSet(++j);
      result.SetElement(i);
    }   
    i++;
  }
  return result;
}

 

// Devuelve un conjunto resultante de hacer la operación
// del complemento al conjunto invocante.
Set
Set::Complement() {
  unsigned int i = 1;
  unsigned int j = 0;
  Set result(1);

  while(i <= (GetSet().size() * 8 * sizeof(long))) {
    if(!BelongToSet(i)) {
      result.ResizeSet(++j);
      result.SetElement(i);
    }
    i++;  
  }
  return result;
}


/* Operaciones de Entrada/Salida */
// Escribe el conjunto invocante.
void
Set::write(ostream& os) {
  int count=1;
  os << "{";  
  
  for(unsigned int i = 1; i <= (8 * sizeof(long) * GetSet().size()); i++)
    if(BelongToSet(i)) {
      if(count < GetNElements()) {
        os << i << ", ";
        count++;
      } 
      else os << i;
    }

  os << "}";
}


// Lee y almacena los datos leídos en el conjunto
// invocante.
void
Set::read(istream& is){
  Set set1, set2;
  char reader, operation = '0';
  bool complement1 = false, complement2 = false;
  int i = 0;

  is >> reader;
  if(reader == '!')
    complement1 = true;

  // Lectura del primer operando
  while(reader != '}') {
    is >> reader;
    if(isdigit(reader))
      i = i*10 + (reader - '0');
    if ((reader == ',' || reader == '}') && (i != 0)) {
      set1.SetElement(i);
      i = 0;
    }
  }  

  // Lectura de la operación
  while((operation != '+') && (operation != '-')
    && (operation != '*') && (operation != '{') && (operation != '!'))
    is >> operation;

  // Si es solo un operando:
  if(operation == '{' || operation == '!') {
    if(complement1) *this = set1.Complement();
    else *this = set1;
    is.unget();
  }
  // Si son 2 operandos:
  else {

  while( reader != '{') {
    if(reader == '!')
      complement2 = true;
    is >> reader;
  }

  // Lectura del segundo operando
  while(reader != '}') {
    is >> reader;
    if(isdigit(reader))
      i = i*10 + (reader - '0');
    if ((reader == ',' || reader == '}') && (i != 0)) {
      set2.SetElement(i);
      i = 0;
    }
  }

  // Realizamos operacion teniendo en cuenta los '!'
  switch(operation) {

    case '+': // UNION
    if (complement1 && complement2) {
      set2 = set2.Complement();
      *this = set1.Complement().Union(set2);
    }
    else if(complement1) {
      *this = set1.Complement().Union(set2);
    }
    else if (complement2) {
      set2 = set2.Complement();
      *this = set1.Union(set2);
    }
    else *this = set1.Union(set2);
    break;

    case '-': // Complemento Relativo    
    if (complement1 && complement2) {
      set2 = set2.Complement();
      *this = set1.Complement().RelativeComplement(set2);
    }
    else if(complement1) {
      *this = set1.Complement().RelativeComplement(set2);
    }
    else if (complement2) {
      set2 = set2.Complement();
      *this = set1.RelativeComplement(set2);
    }
    else *this = set1.RelativeComplement(set2);
    break;

    case '*': // Intersección
    if (complement1 && complement2) {
      set2 = set2.Complement();
      *this = set1.Complement().Intersection(set2);
    }
    else if(complement1) {
      *this = set1.Complement().Intersection(set2);
    }
    else if (complement2) {
      set2 = set2.Complement();
      *this = set1.Intersection(set2);
    }
    else *this = set1.Intersection(set2);
    break;
    
    default:
    cout << "Hubo un error realizando las operaciones."<< endl;
    break;
  }
  }  
}


/* Sobrecarga de operadores */
// Sobrecarga del operador de igualación
Set&
Set::operator=(Set A) {
  CleanElements();
  ResizeSet(A.GetSize());
  conjunto.resize(A.GetSet().size());
 
  for(unsigned int i = 1; i <= (8 * sizeof(long) * A.GetSet().size()); i++)
    if(A.BelongToSet(i))
      SetElement(i);

  return *this;
}


// Sobrecarga del operador de igualdad:
// Retorna '1' si ambos conjuntos son iguales
// y '0' en caso contrario.
bool
Set::operator==(Set& A) {
  if(GetNElements() != A.GetNElements())
    return false;

  unsigned int count = 0;
  for(unsigned int i = 0; i < GetSet().size(); i++) {
    if((conjunto[i] ^ A.conjunto[i]) == 0)  
      count++;
  }
  if(count == GetSet().size()) return true;
  else return false;
}


// Sobrecarga del operador '+' como union
// de conjuntos.
Set
operator+(Set& A, Set& B){
  return A.Union(B);
}


// Sobrecarga del operador '-' como 
// complemento relativo de conjuntos.
Set
operator-(Set& A, Set& B){
  return A.RelativeComplement(B);
}


// Sobrecarga del operador '*' como 
// intersección de conjuntos.
Set
operator*(Set& A, Set& B){
  return A.Intersection(B);
}


// Sobrecarga del operador '!' como
// complemento de un conjunto.
Set
operator!(Set& A){
  return A.Complement();
}


/* Sobrecarga de operadores de E/S */
ostream&
operator<<(ostream& os, Set& A) {
  A.write(os);
  return os;
}



istream&
operator>>(istream& is, Set& A) {
  A.read(is);
  return (is);
}