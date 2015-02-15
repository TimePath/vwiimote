#pragma once

#include "util.hpp"

#pragma pack(push, 1)
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct rumble_t {
    uint8_t value;
};
struct led_t {
    uint8_t value;
};
struct data_report_t {
    uint8_t flags;
    uint8_t mode;
};
struct ir1_t {
    uint8_t value;
};
struct speaker_enable_t {
    uint8_t value;
};
struct status_request_t {
    uint8_t value;
};
struct mem_write_t {
    uint8_t flags;
    uint24_t offset;
    uint8_t size;
    uint8_t data[16];
};
struct mem_read_t {
    uint8_t flags;
    uint24_t offset;
    uint16_t size;
};
struct speaker_data_t {
    uint8_t length;
    uint8_t data[20];
};
struct speaker_mute_t {
    uint8_t value;
};
struct ir2_t {
    uint8_t value;
};

#define REQUESTS(_)                                 \
    /* id, value, type, size */                     \
    _(RUMBLE,           0x10, rumble_t,         1)  \
    _(LED,              0x11, led_t,            1)  \
    _(DATA_REPORT,      0x12, data_report_t,    2)  \
    _(IR1,              0x13, ir1_t,            1)  \
    _(SPEAKER_ENABLE,   0x14, speaker_enable_t, 1)  \
    _(STATUS_REQUEST,   0x15, status_request_t, 1)  \
    _(MEM_WRITE,        0x16, mem_write_t,      21) \
    _(MEM_READ,         0x17, mem_read_t,       6)  \
    _(SPEAKER_DATA,     0x18, speaker_data_t,   21) \
    _(SPEAKER_MUTE,     0x19, speaker_mute_t,   1)  \
    _(IR2,              0x1A, ir2_t,            1)  \
    /**/

struct buttons_t {
    union {
        struct {
            uint16_t left : 1;
            uint16_t right : 1;
            uint16_t down : 1;
            uint16_t up : 1;
            uint16_t plus : 1;
            uint16_t other1 : 1;
            uint16_t other2 : 1;
            uint16_t unknown : 1;
            uint16_t two : 1;
            uint16_t one : 1;
            uint16_t b : 1;
            uint16_t a : 1;
            uint16_t minus : 1;
            uint16_t other3 : 1;
            uint16_t other4 : 1;
            uint16_t home : 1;
        } named;
        uint16_t value;
    };
};

struct accel_t {
    uint8_t x, y, z;
};

struct ext_t {
    uint8_t value[21];
};

struct status_t {
    buttons_t buttons;
    union {
        struct {
                uint8_t low_power : 1;
                uint8_t extension : 1;
                uint8_t speaker : 1;
                uint8_t ir : 1;
                uint8_t led0 : 1;
                uint8_t led1 : 1;
                uint8_t led2 : 1;
                uint8_t led3 : 1;
        } named;
        uint8_t value;
    } flags;
    uint16_t padding;
    uint8_t battery;
};

struct data_t {
    buttons_t buttons;
    uint8_t flags;
    uint16_t address;
    uint8_t data[16];
};

struct return_t {
    buttons_t buttons;
    uint8_t id;
    uint8_t error;
};

struct buttons_accel_t {
    buttons_t buttons;
    accel_t accel;
};

struct buttons_ext_t {
    buttons_t buttons;
    uint8_t extension[8];
};

struct buttons_accel_ir_t {
    buttons_t buttons;
    accel_t accel;
    uint8_t ir[12];
};

struct buttons_ext2_t {
    buttons_t buttons;
    uint8_t extension[19];
};

struct buttons_accel_ext_t {
    buttons_t buttons;
    accel_t accel;
    uint8_t extension[16];
};

struct buttons_ir_ext_t {
    buttons_t buttons;
    uint8_t ir[10];
    uint8_t extension[9];
};

struct buttons_accel_ir_ext_t {
    buttons_t buttons;
    accel_t accel;
    uint8_t ir[10];
    uint8_t extension[6];
};

struct buttons_accel_ir_interleaved_t {
    buttons_t buttons;
    uint8_t accel;
    uint8_t ir[18];
};

#define RESPONSES(_)                                                    \
    /* id, value, type, size */                                         \
    _(STATUS,               0x20, status_t,                         6)  \
    _(DATA,                 0x21, data_t,                           21) \
    _(RETURN,               0x22, return_t,                         4)  \
    _(BUTTONS,              0x30, buttons_t,                        2)  \
    _(BUTTONS_ACCEL,        0x31, buttons_accel_t,                  5)  \
    _(BUTTONS_EXT,          0x32, buttons_ext_t,                    10) \
    _(BUTTONS_ACCEL_IR,     0x33, buttons_accel_ir_t,               17) \
    _(BUTTONS_EXT2,         0x34, buttons_ext2_t,                   21) \
    _(BUTTONS_ACCEL_EXT,    0x35, buttons_accel_ext_t,              21) \
    _(BUTTONS_IR_EXT,       0x36, buttons_ir_ext_t,                 21) \
    _(BUTTONS_ACCEL_IR_EXT, 0x37, buttons_accel_ir_ext_t,           21) \
    _(EXT,                  0x3d, ext_t,                            21) \
    _(BUTTONS_ACCEL_IR_A,   0x3e, buttons_accel_ir_interleaved_t,   21) \
    _(BUTTONS_ACCEL_IR_B,   0x3f, buttons_accel_ir_interleaved_t,   21) \
    /**/

#pragma pack(pop)

#define MSG_ASSERT_SIZE(id, op, def, size) assert_static(sizeof(def) == size, sizeof_##id);

REQUESTS(MSG_ASSERT_SIZE)
RESPONSES(MSG_ASSERT_SIZE)
