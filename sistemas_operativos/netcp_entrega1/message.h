/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación de aplicaciones - Netcp()
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    message.h
 * @version 1.0
 * @date    16-12-2020
 *
 * Este fichero define la estructura implementada para el envio de mensajes
 * entre los sockets.
 */

#pragma once

#include <iostream>
#include <array>

// Estructura del mensaje (Debe ser POD)
struct Message {
  std::array<char, 1024> text;
};