#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800A2BDC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u16 D_80083462;
extern u8 D_80173D88[9];

void func_801721A4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 *state;

    FIELD(arg3, u8, 0x71) &= 0x7F;
    if (!(D_80083462 & 0x2000) &&
        ((func_800A2BDC(arg3) << 16) == 0)) {
        if (FIELD(arg3, u32, 0x1C) & 0x400) {
            register s32 link ASM_REG("$2");

            link = FIELD(arg3, s32, 0x14);
            ASM_KEEP(link);
            if (link >= 0) {
                FIELD(arg3, s32, 0x14) = link | 0x80000000;
                FIELD(arg3, u16, 0x2A) +=
                    (func_800A6D30() & 7) << 9;
            }
        }

        FIELD(arg0, u8, 0x9A) = 0x17;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, u8, 0x9B) = 0;
        FIELD(arg0, u16, 0xA6) = 1;
        FIELD(arg0, u16, 0x96) = 0;

        FIELD(arg2, u16, 0x14) |= 0xC;
        FIELD(arg2, u16, 0x12) -= 0x80;
        state = D_80083460;
        FIELD(state, u16, 0xA)++;
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg2, u8 *, 0x2C) = D_80173D88;
        FIELD(arg2, s32, 0xC) = 0xFFFFFF;
        FIELD(arg2, u16, 0x10) = 0x60;
        func_800A56E0(0x811);
        func_80047784(arg2,
            FIELD(arg2, u8 *, 0x2C)[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
}
