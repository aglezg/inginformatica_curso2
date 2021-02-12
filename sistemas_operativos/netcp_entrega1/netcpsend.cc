/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación de aplicaciones - Netcp()
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    netcpsend.cc
 * @version 1.0
 * @date    16-12-2020
 *
 * Este programa lee el contenido de un archivo "prueba.txt" y lo almacena
 * en una estructura de datos con el objetivo de enviarlo a un determinado
 * puerto del ordenador, en este caso el 1025.  
 * Para ello se emplean sockets como medio de comunicación.
 * 
 * Compilar con:  g++ -g -Wall -o netcpsend netcpsend.cc socket.cc file.cc
 * Ejecutar como: ./netcpsend
 */

#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <system_error>
#include "socket.h"
#include "file.h"
#include "message.h"

int protected_main(int argc, char* argv[]) {
  
  Socket socket_servidor(make_ip_address(0));
  File file("prueba.txt", O_RDONLY, S_IROTH);
  Message message{};
  socket_servidor.send_to(message, make_ip_address(1025));
  return 0;

}

int main (int argc, char* argv[]) {

  try {
    protected_main(argc, argv);
  }
  catch(std::system_error& e) {
    std::cerr << "netcp" << ":" << e.what() << "\n";
    return 1;
  }
  catch(...) {
    std::cout << "netcp: error desconocido.\n";
    return 2;
  }

  Socket socket_servidor(make_ip_address(0));
  Message message{};

  File file("prueba.txt", O_RDONLY, S_IROTH);
  ssize_t n_bytes; 
  
  while (n_bytes != 0) {
    n_bytes = file.read_from(message);
    socket_servidor.send_to(message, make_ip_address(1025));
  }

  return EXIT_SUCCESS;

}