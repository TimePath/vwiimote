#pragma once

#include <netinet/in.h>
#include "util.hpp"

namespace vwiimote {
    class Socket {
        int fd = -1;
    public:
        sockaddr_in addr;

        void close();

        ssize_t read(void *buf, size_t len);

        ssize_t write(void *buf, size_t len);

        Socket(int fd, sockaddr_in addr);
    };

    class ServerSocket {
        int fd = -1;
    public:

        void listen(uint16_t port);

        std::unique_ptr<Socket> accept();

        void close();
    };
}
