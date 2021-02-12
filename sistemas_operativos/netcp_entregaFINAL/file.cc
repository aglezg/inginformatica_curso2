#include "file.h"   

// Constructor: Abre el archivo y lo mapea
File::File(const std::string& pathname, bool writeonly, size_t size) {

  const char* filename = pathname.c_str();

  if (writeonly) { // ESCRITURA: Utilizamos size para conocer el tamaño del archivo

    fd_ = open(filename, O_CREAT | O_RDWR, 0666);
    if (fd_ < 0)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'open()'");
        
    int return_lock = lockf(fd_, F_LOCK, 0);
    if (return_lock < 0)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'flock()'");

    int return_code = ftruncate(fd_, size);
    if (return_code < 0)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'ftruncate()'");

    length_ = size;
    map_ = mmap(nullptr, length_, PROT_WRITE, MAP_SHARED, fd_, 0);
    if (map_ == MAP_FAILED)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'mmap()'");
  
  }

  else { // LECTURA: No hace falta usar size, el tamaño del archivo nos lo da 'length'

    fd_ = open(filename, O_RDWR, 0666);
    if (fd_ < 0)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'open()'");

    int return_lock = lockf(fd_, F_LOCK, 0);
    if (return_lock < 0)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'flock()'");

    struct stat statbuf;
    int return_code = fstat(fd_, &statbuf);
    if (return_code < 0)
      throw std::system_error(errno, std::system_category(), "Fallo en la llamada a 'fstat()'");

    length_ = statbuf.st_size;
    map_ = mmap(nullptr, length_, PROT_READ, MAP_SHARED, fd_, 0);
    if ( map_ == MAP_FAILED)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'mmap()'");
  
  }    
}

// Destructor: Cierra el archivo y lo desmapea.
File::~File(){
  if (fd_ >= 0) {
    munmap(map_, length_);
    lockf(fd_, F_ULOCK, 0);
    close(fd_);
  }
}

//Devolver puntero a map
void*
File::GetPointer(void) {
  return map_;
}

// Devuelve el tamaño mapeado
int
File::GetLength(void) {
  return length_;
}