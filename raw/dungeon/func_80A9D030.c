#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8[];
extern u8 D_80170E7C;
extern u8 D_80174C34[];
extern u8 D_80174C64[];
extern u8 D_80174C6C[];

void func_80172830(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 offset;
    s32 value;
    u16 timer;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        goto end;
    }

    offset = (((FIELD(arg3, u16, 0x2A) >> 9) & 7) + 4) % 8;
    FIELD(arg1, s32, 0x0C) =
        D_8006CCD8[offset] * 3 << 16;
    FIELD(arg1, s32, 0x10) =
        D_8006CCE8[offset] * 3 << 16;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg2, u8 *, 0x2C) = D_80174C34;
    func_80047784(arg2,
        D_80174C34[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    {
        s32 post_state;

        post_state = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, u16, 0x96) = 0;
        post_state++;
        FIELD(arg0, u8, 0x9B) = post_state;
        goto end;
    }

state_1:
    FIELD(arg1, s32, 0x0C) -= FIELD(arg1, s32, 0x0C) >> 2;
    FIELD(arg1, s32, 0x10) -= FIELD(arg1, s32, 0x10) >> 2;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174C64;
    func_80047784(arg2,
        D_80174C64[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    {
        s32 post_state;

        post_state = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, u16, 0x96) = 4;
        post_state++;
        FIELD(arg0, u8, 0x9B) = post_state;
        goto end;
    }

state_2:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    func_800A56E0(0x808);
    FIELD(arg2, u8 *, 0x2C) = D_80174C6C;
    func_80047784(arg2,
        D_80174C6C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 0x14;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    {
        s32 post_state;

        post_state = FIELD(arg0, u8, 0x9B);
        post_state++;
        FIELD(arg0, u8, 0x9B) = post_state;
        goto end;
    }

state_3:
    timer = FIELD(arg0, u16, 0x96);
    value = FIELD(arg1, s32, 0x14);
    timer--;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s16)timer < 12) {
        value += 0x1400;
    } else {
        value += 0x20000;
    }
    FIELD(arg1, s32, 0x14) = value;
    FIELD(arg0, s32, 0x90) += value;

    if ((s16)FIELD(arg0, u16, 0x96) == 0x11) {
        s32 sample;
        s16 *first_base;
        s16 *first_entry;
        s16 *entry;

        offset = FIELD(arg3, u16, 0x2A) >> 8;
        first_base = D_8006CCD8;
        first_entry = (s16 *)((u8 *)first_base + (offset & 0xE));
        sample = *first_entry;
        FIELD(arg1, s32, 0x0C) =
            (sample * 3 << 16) + ((sample * 3 << 16) >> 2);
        entry = (s16 *)((u8 *)&D_8006CCE8 + (offset & 0xE));
        sample = *entry;
        FIELD(arg1, s32, 0x14) = 0xFFF70000;
        FIELD(arg1, s32, 0x10) =
            (sample * 3 << 16) + ((sample * 3 << 16) >> 2);
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) |= 8;
    }

    if (((FIELD(arg2, s8, 4) == 3) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }

    if (((FIELD(arg2, s8, 4) == 5) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg1, s32, 0x0C) =
            ((((FIELD(arg2, u8, 0x24) << 6) + 0x20) << 16) -
             FIELD(arg1, s32, 0)) / (s16)FIELD(arg0, u16, 0x96);
        FIELD(arg1, s32, 0x10) =
            ((((FIELD(arg2, u8, 0x25) << 6) + 0x20) << 16) -
             FIELD(arg1, s32, 4)) / (s16)FIELD(arg0, u16, 0x96);
    }

    if (((s16)FIELD(arg0, u16, 0x96) > 0) &&
        !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x100);
    FIELD(arg0, u8 *, 0x8C) = &D_80170E7C;
    D_8008346C = 0;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        goto end;
    }
    D_800E3DE8[0] = (u8 *)arg3 - 0x20;

end:
    return;
}
