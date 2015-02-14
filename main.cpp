#include "parser.h"
#include <sys/un.h>

using namespace std;

int main() {
    ServerSocket serv = ServerSocket();
    serv.listen(9019);
    loop {
        cout << "waiting" << endl;
        val client = serv.accept();
        if (!client) break;
        cout << "Accept " << client << endl;
        uint8_t buf[128];
        for (ssize_t r; (r = client->read(buf, sizeof buf - 1)) != 0;) {
            if (r < 0) {
                error(errno, errno, "recv");
            }
            var *p = buf;
            assert(*p++ == parser::Destination::REMOTE);
            switch (*p) {
#define REQUEST_PARSE(id, value, size)                                                              \
                case value:                                                                     \
                    cout << "<  0x" << hex << value << " " << #id << " (" << size << ")" << endl;  \
                    p += size;                                                                  \
                    parser::respond(static_cast<parser::Request>(value), client);                                                     \
                    break;
                REQUESTS(REQUEST_PARSE)
                default:
                    cout << "WTF 0x" << hex << (int) *p << endl;
                    break;
            }
            zero(buf);
        }
        cout << "Close " << client << endl;
        client->close();
    }
    serv.close();
    return 1;
}
