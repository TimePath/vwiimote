#include "parser.hpp"

// http://wiibrew.org/wiki/Wiimote
namespace vwiimote {

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

    template<typename T>
    void write(Socket &socket, std::unique_ptr<Message<T>> buf, size_t &length) {
        socket.write(reinterpret_cast<uint8_t *>(buf.get()), length);
        std::cout << " > 0x" << std::hex << (int) buf->op << " " << (Response) buf->op << " (" << std::dec << sizeof buf->data << ")" << std::endl;
    }

    template<typename T>
    std::unique_ptr<Message<T>> pack(Response op, T &payload, size_t &length) {
        std::unique_ptr<Message<T>> msg(new Message<T>);
        memset(msg.get(), 0, length = sizeof *msg);
        msg->destination = CONSOLE;
        msg->op = op;
        msg->data = payload;
        return msg;
    }

#define write(socket, response, struct) do {                \
    size_t length;                                          \
    write(socket, pack(response, struct, length), length);  \
} while(0)

    //template<>
    //void respond(Message<rumble_t> msg, Socket &socket) {
    //}
    //
    //template<>
    //void respond(Message<led_t> msg, Socket &socket) {
    //}
    //
    //template<>
    //void respond(Message<data_report_t> msg, Socket &socket) {
    //}
    //
    //template<>
    //void respond(Message<ir1_t> msg, Socket &socket) {
    //}
    //
    //template<>
    //void respond(Message<speaker_enable_t> msg, Socket &socket) {
    //}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

    template<>
    void respond(Message<status_request_t> msg, Socket &socket) {
        status_t ret;
        zero(ret);
        ret.buttons.value = 1;
        ret.flags.named.extension = 1;
        ret.flags.value = 3;
        ret.battery = 4;
        write(socket, STATUS, ret);
    }

#pragma clang diagnostic pop

    template<>
    void respond(Message<mem_write_t> msg, Socket &socket) {
        std::cout << "-- WRITE " << std::dec << (int) msg.data.size << " bytes" << std::endl;
        return_t ret;
        zero(ret);
        write(socket, RETURN, ret);
    }

    template<>
    void respond(Message<mem_read_t> msg, Socket &socket) {
        std::cout << "-- READ " << std::dec << (int) msg.data.size << " bytes" << std::endl;
        data_t ret;
        zero(ret);
        write(socket, DATA, ret);
    }

    //template<>
    //void respond(Message<speaker_data_t> msg, Socket &socket) {
    //}
    //
    //template<>
    //void respond(Message<speaker_mute_t> msg, Socket &socket) {
    //}
    //
    //template<>
    //void respond(Message<ir2_t> msg, Socket &socket) {
    //}
}
