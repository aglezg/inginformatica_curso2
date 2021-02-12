#include "socket.h"
/* Funciones clase Socket **************************************************************/

// Constructor
Socket::Socket(const sockaddr_in& address) {

  fd_ = socket(AF_INET, SOCK_DGRAM, 0);

  if (fd_ < 0) {
    throw std::system_error(errno, std::system_category(), "no se pudo crear el socket");
  }
  else {
    int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
    if (result < 0) 
      throw std::system_error(errno, std::system_category(), "fallo en la inicialización de 'bind' al crear el socket");
  }

}

// Destructor
Socket::~Socket() {
  close(fd_);
}

// Enviar mensajes
void
Socket::send_to(const Message& message, const sockaddr_in& address) {
  
  int result = sendto(fd_, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
  if (result < 0)
    throw std::system_error(errno, std::system_category(), "fallo en la ejecución de 'sendto'");
}

// Recibir mensajes
void
Socket::receive_from(Message& message, sockaddr_in& address) {

  socklen_t src_len = sizeof(address);

  int result = recvfrom(fd_, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&address), &src_len);
  if (result < 0)
    throw std::system_error(errno, std::system_category(), "fallo en la ejecución de 'recvfrom'");

}

/* Otras funciones  ********************************************************************/

sockaddr_in
make_ip_address(int port, const std::string& ip_address) {
  
  sockaddr_in new_address{};
  new_address.sin_family = AF_INET;
  new_address.sin_port = htons(port);

  if (ip_address.empty()) new_address.sin_addr.s_addr = htonl(INADDR_ANY);
  else                    inet_aton(ip_address.c_str(), &new_address.sin_addr);

  return new_address;
}