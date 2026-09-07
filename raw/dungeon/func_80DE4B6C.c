#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_800A2B5C();
extern s32 func_800A4ACC();
extern s32 func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80174558;

void func_8017236C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    FIELD(arg3, u8, 0x71) = FIELD(arg3, u8, 0x71) & 0x7F;
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            FIELD(arg0, s8, 0x9A) = 0x18;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg0, s8, 0x9B) = 0;
            FIELD(arg2, s32 *, 0x2C) = &D_80174558;
            func_80047784(arg2,
                         *((((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)
                           + (u8 *)&D_80174558),
                         0);
            func_800A4ACC(arg3);
            FIELD(arg3, u8, 0x6D) = FIELD(arg3, u8, 0x6D) - 1;
        }
    }
}
