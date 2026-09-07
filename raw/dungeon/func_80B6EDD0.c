#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170E5C;
extern u8 D_80173D04[];
extern u8 D_80173D34[];

void func_801725D0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 index;
    s32 x_step;
    s32 y_step;
    s32 timer;
    s32 state;
    s32 delta;

    index = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
    x_step = *(s16 *)((u8 *)&D_8006CCD8 + index);
    timer = FIELD(arg0, u16, 0x96) - 1;
    y_step = *(s16 *)((u8 *)&D_8006CCE8 + index);
    state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = timer;

    if (state == 2) {
        goto state_2;
    }
    if ((s32)state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        goto done;
    }
    if (state == 3) {
        goto state_3;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 0xFF;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto done;
    }

    FIELD(arg2, u8 *, 0x2C) = D_80173D34;
    func_80047784(
        arg2,
        D_80173D34[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);

    if (FIELD(arg3, void *, 0x60) != 0) {
        void *linked = FIELD(arg3, void *, 0x60);
        void *entry = FIELD(linked, void *, -0x18);
        FIELD(arg0, s16, 0xA6) = FIELD(entry, u16, 0xA) - 0x34;
    } else {
        FIELD(arg0, s16, 0xA6) =
            func_800BCB04(
                ((FIELD(arg2, u8, 0x24) + x_step) << 6) & 0xFFC0,
                ((FIELD(arg2, u8, 0x25) + y_step) << 6) & 0xFFC0,
                (s16)(FIELD(arg3, u16, 0x88) - 0xA0)) - 0x34;
    }
    FIELD(arg0, u16, 0x96) = 2;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_1:
    FIELD(arg0, u16, 0x92) +=
        (FIELD(arg0, s16, 0xA6) - FIELD(arg1, s16, 0xA)) / 3;
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto done;
    }

    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s16, 0x92) = -0x18;
    FIELD(arg0, u16, 0x96) = 4;
    FIELD(arg1, s32, 0xC) =
        (x_step << 22) / FIELD(arg0, s16, 0x96);
    FIELD(arg1, s32, 0x10) = (y_step << 22) / FIELD(arg0, s16, 0x96);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_2:
    FIELD(arg0, s32, 0x90) +=
        ((FIELD(arg0, s16, 0xA6) - FIELD(arg1, s16, 0xA)) / 3) << 16;
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg0, u16, 0x96) = 10;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_3:
    delta = ((s32)(timer << 16) >> 4) + 0x2000;
    FIELD(arg0, s32, 0x90) -= delta;
    if (FIELD(arg0, s16, 0x96) == 6) {
        func_800A56E0(0x808);
    }
    if (FIELD(arg0, s16, 0x96) == 2) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto done;
    }
    FIELD(arg1, s32, 0xC) = (0 - x_step) << 19;
    FIELD(arg1, s32, 0x10) = (0 - y_step) << 19;
    FIELD(arg1, s32, 0x14) = 0xFFF80000;
    FIELD(arg0, u8, 0x9B) = 0xFF;
    goto done;

state_ff:
    FIELD(arg1, s32, 0x14) += 0x18000;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, s32, 0x1C) |= 0x08000000;
    FIELD(arg0, s32, 0x90) = 0;
    FIELD(arg2, u8 *, 0x2C) = D_80173D04;
    func_80047784(
        arg2,
        D_80173D04[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x100);
    FIELD(arg0, s32 *, 0x8C) = &D_80170E5C;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}

/* MECHANISM: An s32 timer holds the decremented lhu directly in a0, removing
   the narrowing move and its one-word displacement cascade.  A short-lived
   delta local forces the retail sll/sra/addiu order before the 0x90 load;
   natural argument and step lifetimes produce the exact 0x30/s0-s6 frame. */
