/**
 * ULL - Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática - Curso 2
 * Asignatura: Sistemas operativos
 * 
 * @brief   Programación en aplicaciones - Netcp(3)
 * @author  Adrian González Galván (alu0101321219@ull.edu.es)
 * @file    netcp.cc
 * @version 2.0
 * @date    19-01-2020
 *
 * Programa que permite "enviar" y "recibir" ficheros a través de un
 * protocolo de comunicaciones red.
 *  
 * Compilar con: g++ -g -Wall -o netcp netcp.cc socket.cc file.cc -pthread
 * Ejemplo de ejecución: NETCP_DEST_PORT=1025 ./netcp
 */

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <thread>
#include <exception>
#include <atomic>
#include <signal.h>
#include <sys/wait.h>
#include <unordered_map>

#include "socket.h"
#include "file.h"
#include "message.h"

#define MAX_BUFFER 4096 // 4KB

std::atomic_bool quit_receive {false};
std::atomic_bool quit_send    {false};
std::atomic_bool pause_send   {false};
std::atomic_bool quit_menu    {false};

int NETCP_DEST_PORT, NETCP_PORT;
std::string NETCP_DEST_IP;

/******** MANEJADOR DE SEÑALES: SIGINT, SIGTERM y SIGHUP ********/
void ending_signal_manager(std::exception_ptr& eptr, sigset_t& set, std::thread& thread) {
  
  try {
    int signum;
    sigwait(&set, &signum);
    quit_menu = true;
    pthread_kill(thread.native_handle(), SIGUSR1);
    thread.join();
  }
  catch (...) {
  std::cerr << "\n        ending_signal_manager error.\n";
  eptr = std::current_exception();
  }

}

/****** MANEJADOR DE SEÑALES ******/
void signal_manager(int signum) {}

/*************************** NETCSEND ***************************/
void netcpsend(std::exception_ptr& eptr, std::string filename) {

  try {  
 
    // Creación del Socket y del mapeado en memoria
    Socket socket_servidor(make_ip_address(NETCP_PORT, NETCP_DEST_IP));
    File file(filename);

    // Creación del 'paquete' que define nombre, tamaño y md5sum del archivo
    Header header {file.GetLength()};
    strcpy(header.name.data(), filename.c_str());

    // Creación de una tubería para obtener la salida del comando 'md5sum'
    int fds[2];
    int pipe_code = pipe(fds);
    if (pipe_code < 0)
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'pipe()'");
    
    pid_t pid = fork();
    if (pid == 0) { // Proceso hijo: envía a través de la tubería la salida de 'md5sum'

      close (fds[0]);
      dup2(fds[1], STDOUT_FILENO);

      execl("/usr/bin/md5sum", "md5sum", header.name.data(), nullptr);
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'execl()'");
    
    }
    else if (pid > 0) { // Proceso padre

      close(fds[1]);
      char read_buffer[4096];
      char* read_buffer_begin = read_buffer;
      size_t total_bytes_read = 0;
      ssize_t bytes_read = 1;

      while (bytes_read > 0 && total_bytes_read < sizeof(read_buffer)) {
        int bytes_left = sizeof(read_buffer) - total_bytes_read;
        bytes_read = read(fds[0], read_buffer_begin, bytes_left);
        if (bytes_read > 0) {
          read_buffer_begin += bytes_read;
          total_bytes_read += bytes_read;
        }
      }

      close (fds[0]);
      if (bytes_read < 0)
        throw std::system_error(errno, std::system_category(), "fallo en la lectura de la tubería");
      
      int status;
      wait(&status);
      if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
        throw std::system_error(errno, std::system_category(), "la tarea terminó inesperadamente");
      
      std::string md5sum;
      const char* p = read_buffer;
      while ((*p != '\n') && (*p != ' ')) {
        md5sum.push_back(*p);
        p++;
      }

      strcpy(header.md5.data(), md5sum.c_str());
    
    }
    else { // Error en la creación del proceso hijo
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'fork()'");
    }

    // Envío de paquetes
    socket_servidor.send_to(header, make_ip_address(NETCP_DEST_PORT, NETCP_DEST_IP));
    void* ptr = file.GetPointer();
    int size = file.GetLength();

    do {

      while (pause_send);

      if (quit_send) break;

      if (size > MAX_BUFFER) {
        socket_servidor.send_to(ptr, MAX_BUFFER, make_ip_address(NETCP_DEST_PORT, NETCP_DEST_IP));
        ptr = reinterpret_cast<char*>(ptr) + MAX_BUFFER;
        size -= MAX_BUFFER;
      }

      else {
        socket_servidor.send_to(ptr, size, make_ip_address(NETCP_DEST_PORT, NETCP_DEST_IP));
        ptr = reinterpret_cast<char*>(ptr) + size;
        size -= size;
      }

    } while (size != 0);

  }

  // Captura de errores
  catch (std::system_error& e) {
    std::cerr << "\n        send: " << e.what() << "\n";
  }
  catch (std::invalid_argument& e) {
    std::cerr << "\n        send: " << e.what() << "\n";
  }
  catch (std::bad_alloc& e) {
    std::cerr << "\n        send: " << e.what() << "\n";
  }

  catch (...) {
    std::cerr << "\n        send: error desconocido.\n";
    eptr = std::current_exception();
  }

}


/****************************** NETCRECEIVE ******************************/
void netcpreceive(std::exception_ptr& eptr, std::string directory_name) {
  
  try {

    // Creación del directorio donde guardar el archivo enviado
    int result = mkdir(directory_name.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    if ((result < 0) && (errno != EEXIST))  
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'mkdir()'");
    
    // Creación del socket de recepción, del paquete de cabecera, etc.
    Socket socket_cliente(make_ip_address(NETCP_DEST_PORT, NETCP_DEST_IP));
    Header header;
    sockaddr_in client_address {};
    std::string md5sum;
  
    // Bucle infinito de recepción de mensajes
    while (true) {

      md5sum.clear();

      if (quit_receive) break;

      // Recepción del primer paquete (cabecera)
      socket_cliente.receive_from(header, client_address);
      std::string filename = header.name.data();
      std::string rute = directory_name + "/" + filename;

      if (quit_receive) break;

      File file(rute, true, header.length);

      void* ptr = file.GetPointer();
      int size = file.GetLength();

      do { // Recepción del contenido del fichero

        if (quit_receive) break;

        if (size > MAX_BUFFER) {

          socket_cliente.receive_from(ptr, MAX_BUFFER, client_address);
          ptr = reinterpret_cast<char*>(ptr) + MAX_BUFFER;
          size -= MAX_BUFFER;
   
        }

        else {

          socket_cliente.receive_from(ptr, size, client_address);
          ptr = reinterpret_cast<char*>(ptr) + size;
          size -= size;

        }

      } while (size != 0);

      // Creación de una tubería para obtener la salida del comando 'md5sum'
      int fds[2];
      int pipe_code = pipe(fds);
      if (pipe_code < 0)
        throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'pipe()'");
    
      pid_t pid = fork();
      if (pid == 0) { // Proceso hijo: envía a través de la tubería la salida de 'md5sum'

        close (fds[0]);
        dup2(fds[1], STDOUT_FILENO);

        execl("/usr/bin/md5sum", "md5sum", rute.c_str(), nullptr);
        throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'execl()'");
    
      }
      else if (pid > 0) { // Proceso padre

        close(fds[1]);
        char read_buffer[4096];
        char* read_buffer_begin = read_buffer;
        size_t total_bytes_read = 0;
        ssize_t bytes_read = 1;

        while (bytes_read > 0 && total_bytes_read < sizeof(read_buffer)) {
          int bytes_left = sizeof(read_buffer) - total_bytes_read;
          bytes_read = read(fds[0], read_buffer_begin, bytes_left);
          if (bytes_read > 0) {
            read_buffer_begin += bytes_read;
            total_bytes_read += bytes_read;
          }
        }

        close (fds[0]);
        if (bytes_read < 0)
          throw std::system_error(errno, std::system_category(), "fallo en la lectura de la tubería");
      
        int status;
        wait(&status);
        if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
          throw std::system_error(errno, std::system_category(), "la tarea terminó inesperadamente");
      
        const char* p = read_buffer;
        while ((*p != '\n') && (*p != ' ')) {
          md5sum.push_back(*p);
          p++;
        }
      }
    else { // Error en la creación del proceso hijo
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'fork()'");
    }
      // Comparación de las salidas del comando "md5sum" para ambos archivos
      std::cout << "        md5sum [sent]     = " << header.md5.data() << "\n";
      std::cout << "        md5sum [received] = " << md5sum << "\n\n";
    }

  }
  
  // Captura de errores
  catch (std::system_error& e) {
    std::cerr << "\n        receive: " << e.what() << "\n";
  }
  catch (std::invalid_argument& e) {
    std::cerr << "\n        receive: " << e.what() << "\n";
  }
  catch (std::bad_alloc& e) {
    std::cerr << "\n        receive: " << e.what() << "\n";
  }

  catch (...) {
    std::cerr << "\n        receive: error desconocido.\n";
    eptr = std::current_exception();
  }

}

/**************** MENU ****************/
void menu(std::exception_ptr& eptr){
  
  try {

    // Hilos y otras variables
    std::string option, filename, dir_name;
    std::thread thread_send, thread_receive;

    system("clear"); // MENÚ
    std::cout << "\e[1m" << "\n  NETCP: send and receive files.\n\n" << "\e[0m";
    std::cout << "    \e[4m" << "Options:\n\n" << "\e[0m";
    std::cout << "        > send\n";
    std::cout << "        > receive\n";
    std::cout << "        > abort\n";
    std::cout << "        > pause\n";
    std::cout << "        > resume\n";
    std::cout << "        > quit";
  
    while (option != "quit") { // Bucle del menú

      if (quit_menu) break;
    
      sleep(1); // Dar tiempo al receive de imprimir "md5sum"
      std::cout << "\n\n        >> ";
      std::cin >> option;

      if (quit_menu) break;

      if (option == "send") { // SEND
        
        std::cout << "        [filename] >> ";
        std::cin >> filename;
        
        // Tarea 2
        if (thread_send.joinable()) {
          pause_send = false;
          thread_send.join();
        }
        quit_send = false;
        thread_send = std::thread(&netcpsend, std::ref(eptr), filename);

      }

      else if (option == "receive") { // RECEIVE
        
        // Tarea 3
        if (thread_receive.joinable())
          std::cout << "\n        ['receive' está actualmente en ejecución]\n";
        else {
      
          quit_receive = false;
          std::cout << "        [dir_name] >> ";
          std::cin >> dir_name;
          thread_receive = std::thread(&netcpreceive, std::ref(eptr), dir_name);
      
        }
      }

      else if (option == "pause") { // PAUSE
        if(thread_send.joinable()) pause_send = true;
        else std::cout << "        ['send' no se está ejecutando actualmente]";
      }

      else if (option == "resume") { // RESUME
        if (thread_send.joinable()) pause_send = false;
        else std::cout << "        ['send' no se está ejecutando actualmente]";
      }

      else if (option == "abort") { // ABORT [SEND | RECEIVE]
 
        std::string abort_option;
        
        do {
        std::cout << "        [send | receive] >> ";
        std::cin >> abort_option;
        
        if ((abort_option == "send") && (thread_send.joinable())) {
          pause_send = false;
          quit_send = true;
          pthread_kill (thread_send.native_handle(), SIGUSR1);
          thread_send.join();
        }
        else if ((abort_option == "receive") && (thread_receive.joinable())) {
          quit_receive = true;
          pthread_kill (thread_receive.native_handle(), SIGUSR1);
          thread_receive.join();
        }
        else std::cout << "        Try again!\n\n";

        } while ((abort_option != "send") && (abort_option != "receive"));
      }

      else if (option == "quit") { // QUIT
        
        if (thread_receive.joinable()) {
          pause_send = false;
          quit_receive = true;
          pthread_kill (thread_receive.native_handle(), SIGUSR1);
          thread_receive.join();
        }
      
        if (thread_send.joinable()) thread_send.join();
        
        std::cout << "\n";

      }
      else { // INCORRECT OPTION
          std::cout << "        Incorrect option, try again.\n";

      }
    }

  }
  
  // Captura de errores
  catch (std::system_error& e) {
    std::cerr << "\n        menu: " << e.what() << "\n";
  }
  catch (std::invalid_argument& e) {
    std::cerr << "\n        menu: " << e.what() << "\n";
  }
  catch (std::bad_alloc& e) {
    std::cerr << "\n        menu: " << e.what() << "\n";
  }

  catch (...) {
    std::cerr << "\n        menu: error desconocido.\n";
    eptr = std::current_exception();
  }

}

/************** PROTECTED MAIN **************/
int protected_main(int argc, char* argv[]) {

  // Variables de entorno
  if (getenv("NETCP_DEST_IP") != nullptr) NETCP_DEST_IP = getenv("NETCP_DEST_IP");
  
  if (getenv("NETCP_DEST_PORT") != nullptr) NETCP_DEST_PORT = atoi(getenv("NETCP_DEST_PORT"));
  else throw std::invalid_argument("se debe definir como mínimo el puerto destino 'NETCP_DEST_PORT'");
  
  if (getenv("NETCP_PORT") != nullptr) NETCP_PORT = atoi(getenv("NETCP_PORT"));
  else NETCP_PORT = 0;

  pid_t pid = getpid();
  std::cout << "pid = " << pid << "\n";
  std::cout << "ppid = " << getppid() << "\n";

  // Hilos
  std::thread thread_menu, thread_signal;

  // Manejador de señales
  struct sigaction act = {0};
  act.sa_handler = &signal_manager;
  sigaction(SIGUSR1, &act, NULL);

  // Bloqueo de señales SIGINT, SIGTERM y SIGHUP
  sigset_t sigwaitset;
  sigemptyset(&sigwaitset);
  sigaddset(&sigwaitset, SIGINT);
  sigaddset(&sigwaitset, SIGTERM);
  sigaddset(&sigwaitset, SIGHUP);
  pthread_sigmask(SIG_BLOCK, &sigwaitset, NULL);
  
  std::exception_ptr eptr {};
  thread_signal = std::thread(&ending_signal_manager, std::ref(eptr), std::ref(sigwaitset), std::ref(thread_menu));
  thread_signal.detach();

  // Tarea 1
  thread_menu = std::thread(&menu, std::ref(eptr));
  thread_menu.join();

  if (eptr) {
    std::rethrow_exception(eptr);
  }

  return EXIT_SUCCESS;
}

/************** MAIN **************/
int main (int argc, char* argv[]) {

  try {
    return protected_main(argc, argv);
  }
 
  // Captura de errores
  catch (std::system_error& e) {
    std::cerr << "netcp" << ":" << e.what() << "\n";
    return 1;
  }
  catch (std::invalid_argument& e) {
    std::cerr << "netcp: " << e.what() << "\n";
    return 2;
  }
  catch (std::bad_alloc& e) {
    std::cerr << "netcp: " << e.what() << "\n";
    return 3;
  }
  catch (...) {
    std::cerr << "netcp: error desconocido.\n";
    return 99;
  }

}