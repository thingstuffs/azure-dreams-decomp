#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;

void func_80171284(void *arg0, void *arg1, void *arg2) {
    u16 value;
    u16 total;
    s16 age;

    value = FIELD(arg0, u16, 0x24) - 1;
    FIELD(arg0, u16, 0x24) = value;
    if ((s16)value < 8) {
        FIELD(arg0, u16, 0x4E) = FIELD(arg0, u16, 0x4E) - 1;
    }

    if ((s16)FIELD(arg0, u16, 0x4E) < 2) {
        FIELD(arg0, u16, 0x4E) = 2;
    }

    if ((s16)FIELD(arg0, u16, 0x24) < 10) {
        value = FIELD(arg0, u16, 0x2A) + 1;
        total = FIELD(arg0, u16, 0x50) + value;
        FIELD(arg0, u16, 0x2A) = value;
        FIELD(arg0, u16, 0x50) = total;
    } else {
        FIELD(arg0, u16, 0x50) = FIELD(arg0, u16, 0x50) + 1;
    }

    if ((s16)FIELD(arg0, u16, 0x24) < 11) {
        value = FIELD(arg0, u16, 0x2C) + 2;
        FIELD(arg0, u16, 0x2C) = value;
        FIELD(arg1, u16, 0xA) = FIELD(arg1, u16, 0xA) - value;
    }

    age = FIELD(arg0, s16, 0x24);
    if (age < 5) {
        FIELD(arg2, s8, 0xC) = (FIELD(arg0, u8, 2) * age) / 5;
        FIELD(arg2, s8, 0xD) = (FIELD(arg0, u8, 3) * FIELD(arg0, s16, 0x24)) / 5;
        FIELD(arg2, s8, 0xE) = (FIELD(arg0, u8, 4) * FIELD(arg0, s16, 0x24)) / 5;
    }

    if (FIELD(arg0, s16, 0x24) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
