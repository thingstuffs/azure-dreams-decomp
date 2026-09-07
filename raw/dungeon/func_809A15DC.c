#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80173264(void) __attribute__((noreturn));
extern void func_80174DA0(void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_80170868[6];
extern u8 D_801710EC[9];
extern u8 D_80175E78[8];
extern u8 D_80175E80[8];

void func_80172DDC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 6) {
        return;
    }
    (void)keepalive;
    goto *D_80170868[state];

L0:
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_800A56E0(0x80E);
    }
    FIELD(arg0, u8, 0x9B)++;

L1:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, 0x96) = 0x100;
        FIELD(arg0, u8, 0x9B) = 5;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        func_80173264();
    }

    FIELD(arg2, u8, 5) -= 2;
    {
        u32 index = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
        FIELD(arg1, s32, 0x0C) -=
            (s32)*(s16 *)((u8 *)&D_8006CCD8 + index) << 16;
        FIELD(arg1, s32, 0x10) -=
            (s32)*(s16 *)((u8 *)&D_8006CCE8 + index) << 16;
    }
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, u8 *, 0x2C) = D_80175E78;
        func_80047784(
            arg2,
            D_80175E78[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B)++;
    }

L2:
    {
        u16 timer = FIELD(arg0, u16, 0xA2) + 0x10;

        FIELD(arg0, u16, 0xA2) = timer;
        if ((s16)timer >= 0x31) {
            FIELD(arg0, u16, 0xA2) = 0x30;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
        }
    }
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if (FIELD(arg0, s16, 0xA2) < 0x30) {
        return;
    }
    {
        s32 current_state = FIELD(arg0, u8, 0x9B);

        FIELD(arg0, u16, 0x96) = 0;
        if (current_state == 0) {
            return;
        }
    }
    func_800A56E0(0x808);
    FIELD(arg0, u8, 0x9B)++;
    func_80174DA0((u8 *)arg0 - 0x20, (u8 *)arg3 + 0x2A,
                  (u8 *)arg0 + 0x9B);
    func_80173264();

L3:
    {
        u8 *table_x = (u8 *)&D_8006CCD8;
        u8 *table_y = (u8 *)&D_8006CCE8;
        u16 timer;

        FIELD(arg1, s32, 0x0C) +=
            (s32)*(s16 *)(table_x +
                (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 17;

        FIELD(arg1, s32, 0x10) +=
            (s32)*(s16 *)(table_y +
                (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 17;

        FIELD(arg0, s32, 0xA0) -= (s32)FIELD(arg0, s16, 0x96) << 17;
        timer = FIELD(arg0, u16, 0x96) + 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((s16)timer < 9) {
            return;
        }

        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        FIELD(arg2, u8 *, 0x2C) = D_80175E80;
        func_80047784(
            arg2,
            D_80175E80[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        FIELD(arg1, s32, 0x0C) =
            -*(s16 *)(table_x +
                (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 20;

        FIELD(arg1, s32, 0x10) =
            -*(s16 *)(table_y +
                (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 20;
        FIELD(arg0, s32, 0xA8) = FIELD(arg1, s32, 0x0C) / 6;
        FIELD(arg0, s32, 0xAC) = FIELD(arg1, s32, 0x10) / 6;
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        func_80173264();
    }

L4:
    FIELD(arg1, s32, 0x0C) -= FIELD(arg0, s32, 0xA8);
    FIELD(arg1, s32, 0x10) -= FIELD(arg0, s32, 0xAC);
    FIELD(arg0, s32, 0xA0) =
        func_800644B8(FIELD(arg0, s16, 0x96) * 146) * 160 + 0x100000;

L5:
    {
        u16 timer = FIELD(arg0, u16, 0x96) + 1;

        FIELD(arg0, u16, 0x96) = timer;
        if ((s16)timer < 7 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            return;
        }
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x100);
    FIELD(arg0, u8 *, 0x8C) = D_801710EC;
    D_8008346C = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    func_800A4ACC(arg3);
}

/* MECHANISM: The four live args naturally select the retail 0x30 frame and s0-s3,
   while the L3 table bases remain held in s4/s5 across calls.
   Storing both X/Y numerators before their /6 writes exposes the multiply-latency schedule;
   zeroing the timer before incrementing state places retail's final sh before sb. */
