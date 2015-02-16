#include <unistd.h>
#include "transport.hpp"
#include "util.hpp"

namespace vwiimote {

    Socket::Socket(int fd, sockaddr_in addr) {
        this->fd = fd;
        this->addr = addr;
    }

    void Socket::close() {
        ::shutdown(fd, SHUT_RDWR);
        ::close(fd);
    }

    ssize_t Socket::read(void *buf, size_t len) {
        return ::recv(fd, buf, len, 0);
    }

    ssize_t Socket::write(void *buf, size_t len) {
        return ::write(fd, buf, len);
    }

    std::unique_ptr<Socket> ServerSocket::accept() {
        sockaddr_in clientAddr;
        var addrSize = sizeof clientAddr;
        int client = ::accept(fd, (sockaddr *) &clientAddr, (socklen_t *) &addrSize);
        if (client < 0) {
            die("accept");
        }
        return std::unique_ptr<Socket>(new Socket(client, clientAddr));
    }

    void ServerSocket::close() {
        ::close(fd);
    }

// CLion bug
#undef AF_INET
#define AF_INET 2

    void ServerSocket::listen(uint16_t port) {
        val server = socket(AF_INET, SOCK_STREAM, 0);
        if (server < 0) die("socket");

        val reuseAddress = 1;
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuseAddress, sizeof reuseAddress);

        sockaddr_in serverAddr;
        zero(serverAddr);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(server, (sockaddr *) &serverAddr, (socklen_t) sizeof serverAddr) < 0) die("bind");
        if (::listen(server, 1024) < 0) die("listen");
        fd = server;
    }
}
