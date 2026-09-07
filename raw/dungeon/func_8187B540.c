#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 D_8002694C;
extern s32 D_800814A0;

void func_8187B540(void *arg0, s32 arg1, void *arg2) {
    u8 *obj = arg0;
    u8 *page = (u8 *)&D_8002694C - 0x694C;
    u16 value;

    FIELD(arg2, u16, 0x1A) += FIELD(obj, u16, 0xA0);
    value = FIELD(obj, u16, 0x10) - 0x20;
    *(s16 *)(page + 0x694C) = 1;
    FIELD(obj, u16, 0x10) = value;
    if ((s16)value <= 0) {
        FIELD(obj, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
