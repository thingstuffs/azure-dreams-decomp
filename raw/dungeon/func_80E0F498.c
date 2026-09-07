#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801752EC(void *, void *, void *);
extern void func_801755A8(void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80171094[];
extern u8 D_80176488[];

void func_80172C98(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 timer;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    return;

state_zero:
    FIELD(arg0, s16, 0xAE) = 6;
    FIELD(arg1, s32, 0xC) =
        -(((func_80064584(FIELD(arg3, s16, 0x2A)) >> 4) << 13) /
          FIELD(arg0, s16, 0xAE));
    FIELD(arg1, s32, 0x10) =
        -(((func_800644B8(FIELD(arg3, s16, 0x2A)) >> 4) << 13) /
          FIELD(arg0, s16, 0xAE));
    FIELD(arg0, u8, 0x9B)++;

state_one:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg1, s32, 0xC) =
            FIELD(arg1, s32, 0x10) =
                FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        return;
    }

    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer < 0) {
        FIELD(arg1, s32, 0xC) =
            FIELD(arg1, s32, 0x10) =
                FIELD(arg1, s32, 0x14) = 0;
    }

    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        u8 *table = D_80176488;

        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, s16, 0xAE) = 6;
        FIELD(arg1, s32, 0xC) =
            ((func_80064584(FIELD(arg3, s16, 0x2A)) >> 4) << 14) /
            FIELD(arg0, s16, 0xAE);
        FIELD(arg1, s32, 0x10) =
            ((func_800644B8(FIELD(arg3, s16, 0x2A)) >> 4) << 14) /
            FIELD(arg0, s16, 0xAE);
        FIELD(arg0, u16, 0xAE)--;
        func_801752EC(arg0, arg1, arg2);
        func_801755A8(arg0, arg1, arg2);
        func_800A56E0(0x80E);
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg0, u16, 0x96) = 0;
    }
    return;

state_two:
    timer = FIELD(arg0, u16, 0xAE) - 1;
    FIELD(arg0, u16, 0xAE) = timer;
    if ((s16)timer < 0) {
        FIELD(arg1, s32, 0xC) =
            FIELD(arg1, s32, 0x10) =
                FIELD(arg1, s32, 0x14) = 0;
    }

    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((s16)timer == 5) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        func_800A56E0(0x808);
    }

state_three:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg1, s32, 0xC) =
            FIELD(arg1, s32, 0x10) =
                FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg0, u8 *, 0x8C) = D_80171094;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A4ACC(arg3);
    }
}
