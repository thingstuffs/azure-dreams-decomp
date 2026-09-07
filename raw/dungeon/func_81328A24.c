#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016FCE4(void *, s32, s32, void *);
extern void func_800A9A0C(void *);
extern s16 func_800A2BDC(void *);
extern u16 D_80083462;

s32 func_80170224(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    void *base = arg0;
    s16 ret;

    if (FIELD(base, u16, 0xB0) != 0) {
        ret = func_800ADDA0(arg1, arg2, base, 3, 6, (u8 *)base + 0x9C);
        if (ret < 0) {
            ASM_SCHED_BARRIER();
            return 0;
        }
        if (arg3 != 0) {
            func_8016FCE4(base, arg1, arg2, base);
            return 0;
        }
    } else {
        ret = 0;
    }

    switch (ret) {
    case 0:
        FIELD(arg0, u8, 0x9A) = 14;
        func_800A9A0C(base);
        return 0;

    case 2:
        func_8016FCE4(arg0, arg1, arg2, base);
        return 0;

    case 1:
        FIELD(base, u8, 0x71) &= 0x7F;
        if (func_800A2BDC(base) != 0) {
            FIELD(base, u16, 0x46) &= 0x7FFF;
            return 0;
        }
        /* fallthrough */
    default:
        FIELD(base, u8, 0x71) &= 0x7F;
        if (!(D_80083462 & 8)) {
            return 1;
        }
        FIELD(base, u16, 0x46) &= 0x7FFF;
        return 0;
    }
}
