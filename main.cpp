#include "transport.hpp"
#include <sys/un.h>

using namespace std;

int main() {
    ServerSocket serv = ServerSocket();
    serv.listen(1900);
    loop {
        cout << "waiting" << endl;
        val client = serv.accept();
        if (!client) break;
        cout << "Accept " << client << endl;
        {
            char buf[128];
            int r;
            while ((r = client->read(buf, sizeof buf - 1) > 0)) {
                cout << r << " thing: " << buf << endl;
            }
            bzero(&buf, sizeof buf);
            cout << r << endl;
            if (r < 0) {
                error(errno, errno, "recv");
            }
        }
        cout << "Close " << client << endl;
        client->close();
    }
    serv.close();
    return 1;
}
