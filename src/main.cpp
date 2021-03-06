#include "util.hpp"
#include "transport.hpp"
#include "parser.hpp"

template<typename T>
Message<T> read(Destination destination, uint8_t op, uint8_t *data) {
    Message<T> m;
    m.op = op;
    m.destination = destination;
    m.data = *reinterpret_cast<T *>(data);
    return m;
}

int main() {
    ServerSocket serv = ServerSocket();
    serv.listen(9019);
    loop {
        std::cout << "-- Waiting" << std::endl;
        val client = serv.accept();
        if (!client) break;
        std::cout << "-- Accept " << std::dec << client->addr.sin_port << std::endl;
        uint8_t buf[128];
        for (ssize_t r; (r = client->read(buf, sizeof buf - 1)) != 0;) {
            if (r < 0) {
                error(errno, errno, "recv");
            }
            var *p = buf;
            val destination = static_cast<Destination>(*p++);
            assert(destination == Destination::REMOTE);

            val op = *p;
            switch (op) {
#define REQUEST_PARSE(id, value, type, size)                                                        \
                case value:                                                                         \
                    std::cout << "<  0x" << std::hex << (int) value << " " #id << " (" << std::dec << size << ")" << std::endl; \
                    respond(read<type>(destination, op, p), *client);                               \
                    p += size;                                                                      \
                    break;
                REQUESTS(REQUEST_PARSE)
                default:
                    std::cout << "<  0x" << std::hex << op << std::endl;
                    break;
            }
            zero(buf);
        }
        std::cout << "-- Close " << std::dec << client->addr.sin_port << std::endl;
        client->close();
    }
    serv.close();
    return 1;
}
