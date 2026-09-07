#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80024334(void *arg0, void *arg1, void *arg2) {
    void *obj;

    obj = FIELD(arg0, void *, 0);

    if (FIELD(obj, u16, 0x24) & 1) {
        FIELD(arg2, u16, 0x14) |= 0x80;
    } else {
        FIELD(arg2, u16, 0x14) &= 0xFF7F;
    }

    if (FIELD(obj, s32, 0x14) != 0) {
        FIELD(arg2, s32, 0xC) = 0x808080;
    } else {
        FIELD(arg2, s32, 0xC) = 0xFFFFFF;
    }

    if (FIELD(arg0, s16, 8) != 0) {
        FIELD(arg1, u16, 2) = FIELD(obj, u16, 4);
        FIELD(arg1, u16, 6) = FIELD(obj, u16, 6);
        FIELD(arg1, u16, 0xA) = FIELD(obj, u16, 8);
    } else {
        FIELD(arg1, u16, 2) = FIELD(obj, u16, 0xC);
        FIELD(arg1, u16, 6) = FIELD(obj, u16, 0xE);
        FIELD(arg1, u16, 0xA) = FIELD(obj, u16, 0x10);
    }
}
