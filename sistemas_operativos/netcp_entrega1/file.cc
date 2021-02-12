#include "file.h"   

// Constructor
File::File(const char* pathname, int flags, mode_t mode) {

  fd_ = open(pathname, flags, mode);
  if (fd_ < 0)
    throw std::system_error(errno, std::system_category(), "fallo en la apertura del fichero");
}

// Destructor
File::~File(){
  close(fd_);
}

// Escribir en un fichero
ssize_t
File::write_to(Message& message) {

  ssize_t n_bytes = write(fd_, &message, sizeof(message));
  return n_bytes;

}

// Leer de un fichero
ssize_t
File::read_from(Message& message) {
  
  ssize_t n_bytes = read(fd_, &message, sizeof(message));
  return n_bytes;

}