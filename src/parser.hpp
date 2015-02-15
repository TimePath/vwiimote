#pragma once

#include "defs.hpp"
#include "transport.hpp"
#include "util.hpp"

enum Destination : uint8_t {
    CONSOLE = 0xA1, // HIDP_TRANS_DATA | HIDP_DATA_RTYPE_INPUT
    REMOTE = 0xA2 // HIDP_TRANS_DATA | HIDP_DATA_RTYPE_OUPUT
};

#pragma pack(push, 1)

template<typename T>
struct Message {
    Destination destination;
    uint8_t op;
    T data;
};

#pragma pack(pop)

#define MSG_ENUM(id, value, type, size) id = value,

enum Request : uint8_t {
    REQUESTS(MSG_ENUM)
};

enum Response : uint8_t {
    RESPONSES(MSG_ENUM)
};

#define MSG_CONCAT(id, value, type, size)   \
        case id:                            \
            os << #id;                      \
            break;

inline std::ostream &operator<<(std::ostream &os, Request r) {
    switch (r) {
        REQUESTS(MSG_CONCAT)
        default:
            os.setstate(std::ios_base::failbit);
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, Response r) {
    switch (r) {
        RESPONSES(MSG_CONCAT)
        default:
            os.setstate(std::ios_base::failbit);
    }
    return os;
}

template<class T>
void respond(Message<T> msg, Socket &socket) {
    std::cout << "-- Unimplemented " << static_cast<Request>(msg.op) << std::endl;
}

