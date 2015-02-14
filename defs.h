#pragma once

#define REQUESTS(_)                     /**/\
    _(NOP,                  0x00, 0)    /**/\
    _(RUMBLE,               0x10, 1)    /**/\
    _(LED,                  0x11, 1)    /**/\
    _(DATA_REPORT,          0x12, 2)    /**/\
    _(IR1,                  0x13, 1)    /**/\
    _(SPEAKER_ENABLE,       0x14, 1)    /**/\
    _(STATUS_REQUEST,       0x15, 1)    /**/\
    _(MEM_WRITE,            0x16, 21)   /**/\
    _(MEM_READ,             0x17, 6)    /**/\
    _(SPEAKER_DATA,         0x18, 21)   /**/\
    _(SPEAKER_MUTE,         0x19, 1)    /**/\
    _(IR2,                  0x1A, 1)    /**/\
    /**/

#define RESPONSES(_)                    /**/\
    _(STATUS,               0x20, 6)    /**/\
    _(DATA,                 0x21, 21)   /**/\
    _(RETURN,               0x22, 4)    /**/\
    _(BUTTONS,              0x30, 2)    /* 2B */\
    _(BUTTONS_ACCEL,        0x31, 5)    /* 2B 3A */\
    _(BUTTONS_EXT,          0x32, 10)   /* 2B 8E */\
    _(BUTTONS_ACCEL_IR,     0x33, 17)   /* 2B 3A 12I */\
    _(BUTTONS_EXT2,         0x34, 21)   /* 2B 19E */\
    _(BUTTONS_ACCEL_EXT,    0x35, 21)   /* 2B 3A 16E */\
    _(BUTTONS_IR_EXT,       0x36, 21)   /* 2B 10I 9E */\
    _(BUTTONS_ACCEL_IR_EXT, 0x37, 21)   /* 2B 3A 10I 6E */\
    _(EXT,                  0x3d, 21)   /* 21E */\
    _(BUTTONS_ACCEL_IR_A,   0x3e, 21)   /* 2B 1A 18I */\
    _(BUTTONS_ACCEL_IR_B,   0x3f, 21)   /* 2B 1A 18I */\
    /**/
