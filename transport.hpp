#pragma once

#include <glob.h>
#include <monetary.h>
#include <printf.h>
#include "util.hpp"

class Socket {
    int fd = -1;
public:

    void close();

    ssize_t read(void *buf, size_t i);
};

class ServerSocket {
    int fd = -1;
public:

    void listen(uint16_t port);

    Socket *accept();

    void close();
};
