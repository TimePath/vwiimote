#include <sys/un.h>
#include <bits/unique_ptr.h>
#include "parser.h"

// http://wiibrew.org/wiki/Wiimote

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#pragma pack(push, 1)
template<typename T>
struct Message {
    parser::Destination destination;
    uint8_t op;
    T data;
};

template<typename T>
void write(Socket &socket, std::unique_ptr<Message<T>> buf, size_t &length) {
    socket.write(reinterpret_cast<uint8_t *>(buf.get()), length);
    std::cout << " > " << "0x" << std::hex << (int) buf->op << " " << (parser::Response) buf->op << " (" << sizeof buf->data << ")" << std::endl;
}

template<typename T>
std::unique_ptr<Message<T>> pack(parser::Response op, T &payload, size_t &length) {
    std::unique_ptr<Message<T>> msg(new Message<T>);
    memset(msg.get(), 0, length = sizeof *msg);
    msg->destination = parser::CONSOLE;
    msg->op = op;
    msg->data = payload;
    return msg;
}

#define write(socket, response, struct) do {                \
    size_t length;                                          \
    write(socket, pack(response, struct, length), length);  \
} while(0)

void parser::respond(Request op, const Socket *socket) {
    Socket s = *socket;
#define REQUEST_RESPOND(id, value, size)    \
        case value:                         \
            parser::respond_##id(s);        \
            break;
    switch ((uint8_t) op) {
        REQUESTS(REQUEST_RESPOND)
        default:
            break;
    }
}

void parser::respond_NOP(Socket &socket) {
}

void parser::respond_RUMBLE(Socket &socket) {
}

void parser::respond_LED(Socket &socket) {
}

void parser::respond_DATA_REPORT(Socket &socket) {
}

void parser::respond_IR1(Socket &socket) {
}

void parser::respond_SPEAKER_ENABLE(Socket &socket) {
}

void parser::respond_STATUS_REQUEST(Socket &socket) {
    struct {
        int16_t buttons;
        union {
            struct {
                uint8_t leds : 4;
                uint8_t flags : 4;
            } bits;
            uint8_t ledflags;
        };
        uint16_t padding;
        uint8_t battery;
    } status;
    zero(status);
    status.buttons = 1;
    status.bits.leds = 2;
    status.bits.flags = 3;
    status.battery = 4;
    write(socket, STATUS, status);
}

void parser::respond_MEM_WRITE(Socket &socket) {
}

void parser::respond_MEM_READ(Socket &socket) {
}

void parser::respond_SPEAKER_DATA(Socket &socket) {
}

void parser::respond_SPEAKER_MUTE(Socket &socket) {
}

void parser::respond_IR2(Socket &socket) {
}

#pragma pack(pop)
