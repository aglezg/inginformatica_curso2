/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación en aplicaciones - Netcp(3)
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    message.h
 * @version 2.0
 * @date    19-01-2020
 *
 * Este fichero define la estructura implementada para el envio de mensajes
 * que contienen información sobre los archivos mapeados en memoria.
 */

#pragma once

#include <iostream>
#include <array>
#include <atomic>
#include <thread>

// Estructura del mensaje de información (Debe ser POD)
struct Header {
  int length;
  std::array<char, 32> name;
  std::array<char, 64> md5;
};