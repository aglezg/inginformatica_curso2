/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación en aplicaciones - Netcp(3)
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    file.h
 * @version 2.0
 * @date    19-01-2020
 *
 * Este fichero define la clase File, la cual gestiona el descriptor de
 * archivo con el fin de mapear un archivo en memoria.
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
#include <sys/mman.h>

#include "message.h"

// Clase File
class File {

  public:
    
    File(const std::string& pathname, bool writeonly = false, size_t size = 0);
    ~File();

    void*   GetPointer(void);
    int     GetLength(void);

  private:
    
    int fd_ = -1;
    void *map_ = nullptr;
    int length_;

};