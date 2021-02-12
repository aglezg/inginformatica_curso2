#include "socket.h"

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

// Getter
int
Socket::GetDescriptor(void) {
  return fd_;
}

// Enviar mensajes

void
Socket::send_to(const Header& header, const sockaddr_in& address) {
  
  int result = sendto(fd_, &header, sizeof(header), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
  if ((result < 0) && (errno != EINTR))
    throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'sendto()'");
}

void
Socket::send_to(void* pointer, int size, const sockaddr_in &address) {

    int result = sendto(fd_, pointer, size, 0, reinterpret_cast<const sockaddr *>(&address), sizeof(address));
    if ((result < 0) && (errno != EINTR))
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'sendto()'");

}

// Recibir mensajes

void
Socket::receive_from(Header& header, sockaddr_in& address) {
  
  socklen_t src_len = sizeof(address);

  int result = recvfrom(fd_, &header, sizeof(header), 0, reinterpret_cast<sockaddr*>(&address), &src_len);
  if ((result < 0) && (errno != EINTR))
    throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'recvfrom()'");

}

void
Socket::receive_from(void* pointer, int size, sockaddr_in &address) {
  
  socklen_t src_len = sizeof(address);

    int result = recvfrom(fd_, pointer, size, 0, reinterpret_cast<sockaddr*>(&address), &src_len);
    if ((result < 0) && (errno != EINTR))
      throw std::system_error(errno, std::system_category(), "fallo en la llamada a 'recvfrom()'");
    
}

/* Otras funciones  ********************************************************************/

sockaddr_in
make_ip_address(int port, const std::string& ip_address) {
  
  sockaddr_in new_address{};
  new_address.sin_family = AF_INET;
  new_address.sin_port = htons(port);

  if (ip_address.empty()) new_address.sin_addr.s_addr = htonl(INADDR_ANY);
  else               inet_aton(ip_address.c_str(), &new_address.sin_addr);

  return new_address;
}