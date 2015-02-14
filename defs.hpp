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
    uint16_t offset1;
    uint8_t offset2;
    uint8_t size;
    uint8_t data[16];
};
struct mem_read_t {
    uint8_t flags;
    uint16_t offset1;
    uint8_t offset2;
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

#define REQUESTS(_)                                      /**/\
    _(RUMBLE,               0x10, rumble_t,         1)   /**/\
    _(LED,                  0x11, led_t,            1)   /**/\
    _(DATA_REPORT,          0x12, data_report_t,    2)   /**/\
    _(IR1,                  0x13, ir1_t,            1)   /**/\
    _(SPEAKER_ENABLE,       0x14, speaker_enable_t, 1)   /**/\
    _(STATUS_REQUEST,       0x15, status_request_t, 1)   /**/\
    _(MEM_WRITE,            0x16, mem_write_t,      21)  /**/\
    _(MEM_READ,             0x17, mem_read_t,       6)   /**/\
    _(SPEAKER_DATA,         0x18, speaker_data_t,   21)  /**/\
    _(SPEAKER_MUTE,         0x19, speaker_mute_t,   1)   /**/\
    _(IR2,                  0x1A, ir2_t,            1)   /**/\
    /**/

struct status_t {
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
};

struct empty_t {
};

#define RESPONSES(_)                                     /* */\
    _(STATUS,               0x20, status_t,         6)   /* */\
    _(DATA,                 0x21, empty_t,          21)  /* */\
    _(RETURN,               0x22, empty_t,          4)   /* */\
    _(BUTTONS,              0x30, empty_t,          2)   /* 2B */\
    _(BUTTONS_ACCEL,        0x31, empty_t,          5)   /* 2B 3A */\
    _(BUTTONS_EXT,          0x32, empty_t,          10)  /* 2B 8E */\
    _(BUTTONS_ACCEL_IR,     0x33, empty_t,          17)  /* 2B 3A 12I */\
    _(BUTTONS_EXT2,         0x34, empty_t,          21)  /* 2B 19E */\
    _(BUTTONS_ACCEL_EXT,    0x35, empty_t,          21)  /* 2B 3A 16E */\
    _(BUTTONS_IR_EXT,       0x36, empty_t,          21)  /* 2B 10I 9E */\
    _(BUTTONS_ACCEL_IR_EXT, 0x37, empty_t,          21)  /* 2B 3A 10I 6E */\
    _(EXT,                  0x3d, empty_t,          21)  /* 21E */\
    _(BUTTONS_ACCEL_IR_A,   0x3e, empty_t,          21)  /* 2B 1A 18I */\
    _(BUTTONS_ACCEL_IR_B,   0x3f, empty_t,          21)  /* 2B 1A 18I */\
    /**/

#pragma pack(pop)
