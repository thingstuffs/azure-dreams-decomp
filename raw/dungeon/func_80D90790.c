#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80047784();
extern void func_8009C93C();
extern void func_80172050(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_8017386C[];

void func_80171F90(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    FIELD(arg3, u8, 0x71) &= 0x7F;

    if (!(D_80083462 & 0x2000) &&
        ((func_800A2B5C(arg3) << 0x10) == 0) &&
        (func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300),
         ((func_800A2B5C(arg3) << 0x10) == 0))) {
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, s8, 0x9B) = 0;

        if (FIELD(arg0, u16, 0x98) & 0x8000) {
            FIELD(arg0, u8, 0x9A) = 0x17;
            FIELD(arg3, s8, 0x84) = 0x10;
            FIELD(arg3, s8, 0x85) = 0x10;
            func_80172050();
        }

        FIELD(arg0, u8, 0x9A) = 0x11;
        FIELD(arg3, s8, 0x84) = 0x7C;
        FIELD(arg3, s8, 0x85) = 0;
        ASM_SCHED_BARRIER();
        FIELD(arg2, u8 *, 0x2C) = D_8017386C;
        func_80047784(arg2,
                      D_8017386C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                      0);
        FIELD(arg3, u8, 0x6D)--;

        if (FIELD(arg0, u8, 0x9A) == 0x11) {
            func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
        }
    }
}
