#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_8003DB94(void *arg0, void *arg1, s32 arg2);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008CBD4(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80096384(void);
extern void func_80097A48(void) __attribute__((noreturn));
extern void func_800AD4D0(void *arg0);

extern s16 D_80083228[5];
extern s32 D_80083460[5];
extern void *D_800DD274[8];

void func_80097934(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 value;
    s32 *global;

    if (FIELD(arg0, u8, 0x9B) == 0) {
        func_800AD4D0(arg3);
        FIELD(arg0, u8, 0x9B)++;
    }

    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg2, void *, 0x2C) = D_800DD274;
        func_8003DB94(
            arg2,
            D_800DD274[
                ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        global = D_80083460;
        value = global[4];
        if (value == (u32)((u8 *)arg3 - 0x20)) {
            global[4] = value & 0x7FFFFFFF;
        }

        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg3, u8, 0x28) = 0;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_80042B68(arg3, 10);
            func_8008CBD4(arg0, arg1, arg2, arg3);
            func_80097A48();
        }

        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, void *, 0x8C) = func_80096384;
    }
}
