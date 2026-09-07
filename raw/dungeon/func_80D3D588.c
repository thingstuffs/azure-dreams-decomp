#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern s32 func_8009C93C();
extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80172E88(void) __attribute__((noreturn));
extern void func_80175F44();
extern u16 D_80083462;

void func_80172D88(void *arg0, s32 arg1, s32 arg2, void *arg3)
{
    if (FIELD(arg0, u8, 0xB5) == 0) {
        FIELD(arg3, u8, 0x71) &= 0x7F;
        if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 16) == 0)) {
            func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
            if ((func_800A2B5C(arg3) << 16) == 0) {
                FIELD(arg0, s32, 0x8C) = 0;
                FIELD(arg0, s8, 0x9A) = 0x11;
                FIELD(arg0, s8, 0x9B) = 0;
                FIELD(arg0, s16, 0x96) = 0;
                FIELD(arg3, u8, 0x6D)--;
                FIELD(arg0, u16, 0x98) |= 8;
                func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
                FIELD(arg3, s8, 0x84) = 0x7C;
                FIELD(arg3, s8, 0x85) = 0;
                func_80172E88();
            }
        }
    } else {
        func_80175F44(arg0, arg1, arg2, 1, 1);
    }
}
