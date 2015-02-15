#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "util.hpp"

namespace bluetooth {

    val CLASS = 0x000508;
    val NAME = "Nintendo RVL-CNT-01-TR";

    void setup() {
        val timeout = 2000;
        val hdev = hci_get_route(NULL);
        if (hdev < 0) {
            error(errno, errno, "hci_get_route");
        }
        val s = hci_open_dev(hdev);
        if (s < 0) {
            error(errno, errno, "hci_open_dev");
        }
        if (hci_write_class_of_dev(s, (uint32_t) CLASS, timeout) < 0) {
            error(errno, errno, "hci_write_class_of_dev");
        }
        if (hci_write_local_name(s, NAME, timeout) < 0) {
            error(errno, errno, "hci_write_local_name");
        }
        if (hci_write_inquiry_scan_type(s, SCAN_PAGE | SCAN_INQUIRY, timeout) < 0) {
            error(errno, errno, "hci_write_inquiry_scan_type");
        }
    }
}
