/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación de aplicaciones - Netcp()
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    netcpreceive.cc
 * @version 1.0
 * @date    16-12-2020
 *
 * Este programa escucha un puerto de la máquina local (en este caso el
 * 1025) para guardar en una estructura de datos el mensaje que recibe con
 * el principal objetivo de mostrarlo por pantalla.
 * 
 * Compilar con:  g++ -g -Wall -o netcpreceive netcpreceive.cc socket.cc file.cc
 * Ejecutar como: ./netcpreceive
 */

#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "socket.h"
#include "file.h"
#include "message.h"

int protected_main(int argc, char* argv[]) {
  
  Socket socket_cliente(make_ip_address(1025));
  Message message{};
  sockaddr_in client_address{};
  socket_cliente.receive_from(message, client_address);
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
    return 99;
  }

  Socket socket_cliente(make_ip_address(1025));
  Message message;

  sockaddr_in client_address{};
  socket_cliente.receive_from(message, client_address); // Falta bucle?
  std::cout << message.text.data();

  return EXIT_SUCCESS;

}