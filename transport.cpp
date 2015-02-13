#include "transport.hpp"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/un.h>

void Socket::close() {
    ::shutdown(fd, SHUT_RDWR);
    ::close(fd);
}

ssize_t Socket::read(void *buf, size_t len) {
    return recv(fd, buf, len, 0);
}

Socket *ServerSocket::accept() {
    sockaddr_in clientAddr;
    var addrSize = sizeof clientAddr;
    int client = ::accept(fd, (sockaddr *) &clientAddr, (socklen_t *) &addrSize);
    if (client < 0) {
        error(errno, errno, "accept");
    }
    return new Socket;
}

void ServerSocket::close() {
    ::close(fd);
}

// CLion bug
#undef AF_INET
#define AF_INET 2

void ServerSocket::listen(uint16_t port) {
    val reuseAddress = 1;

    val server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) error(EIO, EIO, "Error creating socket");

    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuseAddress, (socklen_t) sizeof reuseAddress);

    sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof serverAddr);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (sockaddr *) &serverAddr, (socklen_t) sizeof serverAddr) < 0) error(errno, errno, "bind");
    if (::listen(server, 1024) < 0) error(errno, errno, "listen");
    fd = server;
}
