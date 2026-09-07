#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_801711A4;
extern u8 D_8017419C[];
extern u8 D_801741A4[];

void func_801724F4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v1;
    s32 temp_a0;
    s32 state;

    temp_v1 = ((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
    temp_s3 = *(s16 *)((u8 *)&D_8006CCD8 + temp_v1);
    temp_s4 = *(s16 *)((u8 *)&D_8006CCE8 + temp_v1);
    state = FIELD(arg0, u8, 0x9B);
    temp_a0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_a0;

    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 0xFF;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto done;
    }
    FIELD(arg2, void *, 0x2C) = D_8017419C;
    func_80047784(arg2,
        D_8017419C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    goto increment_state;

state_one:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg2, void *, 0x2C) = D_801741A4;
        func_80047784(arg2,
            D_801741A4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg1, s32, 0xC) = (temp_s3 << 18) + (temp_s3 << 17);
        FIELD(arg1, s32, 0x10) = (temp_s4 << 18) + (temp_s4 << 17);
        FIELD(arg0, u16, 0x96) = 8;
        func_800A56E0(0x607);
increment_state:
        FIELD(arg0, u8, 0x9B)++;
    }
    goto done;

state_two:
    if ((temp_a0 << 16) <= 0) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        FIELD(arg0, u8, 0x9B) = 0xFF;
    }
    goto done;

state_ff:
    {
        s32 coord = FIELD(arg2, u8, 0x24) << 6;
        s32 current = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0xC) = ((coord - current) << 0xF) >> 1;
    }
    {
        s32 coord = FIELD(arg2, u8, 0x25) << 6;
        s32 current = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) = ((coord - current) << 0xF) >> 1;
    }
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg3, u32, 0x1C) |= 0x40000;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 0x100);
        FIELD(arg0, void *, 0x8C) = &D_801711A4;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        if (FIELD(arg3, s8, 0x6D) == 0) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)arg3 - 0x20;
        }
    }

done:
    return;
}
