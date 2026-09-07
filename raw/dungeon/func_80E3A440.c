#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784();
extern s32 func_800A2BDC();
extern void func_80173D20(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u8 D_80176670[16];

void func_80173C40(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 *state = D_80083460;

    if (FIELD(state, u16, 2) & 0x2000) {
        FIELD(arg3, u8, 0x71) &= 0x7F;
        func_80173D20();
    }

    if ((func_800A2BDC(arg3) << 16) == 0) {
        s32 index;

        FIELD(arg0, s8, 0x9A) = 0x17;
        FIELD(arg0, s8, 0x9B) = 0;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg2, u8 *, 0x2C) = D_80176670;

        index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80176670[index], 0);

        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg3, s32, 0x1C) |= 0x10000000;
        FIELD(state, u16, 0xA)++;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }
}
