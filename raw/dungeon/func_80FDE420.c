#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A5720(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170854[];
extern u8 D_80170874[];
extern u8 D_80170EA8;
extern u8 D_80174090[];
extern u8 D_80174098[];
extern u8 D_801740A0[];

void func_80173C20(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 saved;
    s32 value;
    s32 index;
    u16 timer;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto end;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto end;

state_zero:
    saved = func_800990FC();
    if ((FIELD(arg3, u16, 0x2A) >> 9) & 1) {
        func_80099290(func_80099194(
            D_80170854, func_80099734(arg3, saved)));
    } else {
        func_80099290(func_80099194(
            D_80170874, func_80099734(arg3, saved)));
    }
    func_800A5720(saved);

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto end;
    }

    FIELD(arg2, void *, 0x2C) = D_80174090;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_80174090[index & 7], 0);
    FIELD(arg0, s32, 0x90) = 0;
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg1, s32, 0x14) = 0xFFF00000;
    goto increment_state;

state_one:
    value = FIELD(arg1, s32, 0x14) + 0x20000;
    FIELD(arg1, s32, 0x14) = value;
    FIELD(arg0, s32, 0x90) += value;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }

    FIELD(arg2, void *, 0x2C) = D_80174098;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_80174098[index & 7], 0);
    FIELD(arg0, u16, 0x96) = 8;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg0, u8, 0x9B)++;
    goto end;

state_two:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((timer << 16) == 0) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }

    FIELD(arg2, void *, 0x2C) = D_801740A0;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_801740A0[index & 7], 0);

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto end;

state_three:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800AD594(arg3, 0x1000);
    FIELD(arg0, void *, 0x8C) = &D_80170EA8;
    D_8008346C = 0;
    func_800A4ACC(arg3);

    if (FIELD(arg0, u16, 0x98) & 0x4000) {
        FIELD(arg3, u32, 0x1C) |= 0x1000;
    } else {
        FIELD(arg3, u32, 0x1C) &= ~0x1000;
    }
    FIELD(arg3, u8, 3) = FIELD(arg0, u8, 0xAC);
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        goto end;
    }
    D_800E3DE8 = (u8 *)arg3 - 0x20;

end:
    return;
}
