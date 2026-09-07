#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern u8 D_80083160[];

void *func_800A2000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *obj = func_8003FD64(0x136, arg0 - 0x20);
    void *display;
    void *payload;

    if (obj == 0) {
        return 0;
    }
    display = FIELD(obj, void *, 0xC);
    FIELD(obj, s32, 0x10) = arg4;
    FIELD(obj, s32, 0x20) = arg5;
    payload = (u8 *)obj + 0x20;
    FIELD(payload, s32, 0x10) = arg0;
    FIELD(payload, s32, 0x14) = arg2;
    FIELD(payload, s16, 0x20) = arg3;
    FIELD(payload, s32, 0x40) = arg1;
    FIELD(display, s16, 0x20) = 0x1000;
    FIELD(display, s16, 0x1E) = 0x1000;
    FIELD(display, s16, 0x1C) = 0x1000;
    FIELD(display, s16, 0x12) = 0;
    FIELD(display, s16, 0x14) = 0;
    FIELD(display, s16, 0x10) = 0;
    FIELD(display, u8, 0xC) = D_80083160[0xA8];
    FIELD(display, u8, 0xD) = D_80083160[0xA9];
    FIELD(display, u8, 0xE) = D_80083160[0xAA];
    FIELD(display, s16, 0x14) = 0;
    return obj;
}
