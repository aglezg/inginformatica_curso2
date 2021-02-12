/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación de aplicaciones - Netcp()
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    socket.h
 * @version 1.0
 * @date    16-12-2020
 *
 * Este fichero define la clase Socket, la cual encapsula los descriptores
 * de archivos de los sockets junto con las llamadas al sistema que los
 * manejan, con el fin de que podamos programarlos de forma más sencilla.
 */

#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include "message.h"

// Clase Socket
class Socket {

  public:
    Socket(const sockaddr_in& address);
    ~Socket();

    void send_to(const Message& message, const sockaddr_in& address);
    void receive_from(Message& message, sockaddr_in& address);

  private:
    int fd_;
};

sockaddr_in
make_ip_address(int port, const std::string& ip_address = std::string());