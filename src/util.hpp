#pragma once

#include <assert.h>
#include <bits/unique_ptr.h>
#include <error.h>
#include <iostream>
#include <stdint.h>
#include <sys/un.h>

namespace vwiimote {
#define var auto
#define val const var
#define loop for(;;)

#define _STR(s) #s
#define STR(s) _STR(s)
#define die(reason) error(errno, errno, (__FILE__ ":" STR(__LINE__) ":" + std::string(__func__) + " " reason).c_str())

    template<typename T>
    void zero(T &s) {
        memset(&s, 0, sizeof s);
    }

#define assert_static(e, name) enum { __assert_##name = 1/(e) }

    struct uint24_t {
        uint8_t data[3];

        uint24_t() {
            memset(data, 0, sizeof(data));
        }

        uint24_t(int i) {
            memcpy(data, &i, sizeof(data));
        }

        operator uint32_t() {
            uint32_t ret;
            memcpy(&ret, data, sizeof(data));
            return ret;
        }
    };
}
