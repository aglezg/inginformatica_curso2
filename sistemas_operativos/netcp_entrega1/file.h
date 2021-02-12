/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación de aplicaciones - Netcp()
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    file.h
 * @version 1.0
 * @date    16-12-2020
 *
 * Este fichero define la clase File, la cual gestiona el descriptor de
 * archivo con el fin de facilitar la gestión del recurso "archivo abierto".
 * A su vez cuenta con métodos que permiten leer y escribir el contenido en estos.
 */

#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <system_error>
#include "message.h"

// Clase File
class File {

  public:
  File(const char* pathname, int flags, mode_t mode);
  ~File();
  
  ssize_t write_to(Message& message);
  ssize_t read_from(Message& message);

  private:
    int fd_;

};