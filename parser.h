#pragma once

#include <glob.h>
#include "defs.h"
#include "transport.hpp"

namespace parser {

    enum Destination : uint8_t {
        CONSOLE = 0xA1,
        REMOTE = 0xA2
    };

#define REQUEST_RESPOND_PROTOTYPE(id, value, size) void respond_##id(Socket &socket);

    REQUESTS(REQUEST_RESPOND_PROTOTYPE)

    enum Request : uint8_t {
#define REQUEST_ENUM(id, value, size) id = value,
        REQUESTS(REQUEST_ENUM)
    };

    inline std::ostream &operator<<(std::ostream &os, Request r) {
#define REQUEST_STRING(id, value, size)     \
        case id:                            \
            os << #id;                      \
            break;
        switch (r) {
            REQUESTS(REQUEST_STRING)
            default:
                os.setstate(std::ios_base::failbit);
        }
        return os;
    }

    void respond(Request value, const Socket *socket);

    enum Response : uint8_t {
#define RESPONSE_ENUM(id, value, size) id = value,
        RESPONSES(RESPONSE_ENUM)
    };

    inline std::ostream &operator<<(std::ostream &os, Response r) {
#define RESPONSE_STRING(id, value, size)    \
        case id:                            \
            os << #id;                      \
            break;
        switch (r) {
            RESPONSES(RESPONSE_STRING)
            default:
                os.setstate(std::ios_base::failbit);
        }
        return os;
    }

}
