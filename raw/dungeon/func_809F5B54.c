#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, u8, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171400[];
extern u8 D_80175148[];
extern u8 D_80175158[];

void func_80173354(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer_signed;
    s32 direction;
    s32 x;
    s32 y;
    s32 rounded_x;
    s32 rounded_y;

    direction = (FIELD(arg3, u16, 0x6A) >> 9) & 7;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        func_800AD4D0(arg3);
        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_800AAA54(arg0, arg1, arg2, D_80175158);
            return;
        }

        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }

        FIELD(arg1, s32, 0x0C) = ((s16 *)&D_8006CCD8)[direction] << 18;
        FIELD(arg1, s32, 0x10) = ((s16 *)&D_8006CCE8)[direction] << 18;
        FIELD(arg1, s32, 0x14) = 0x40000;
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
        FIELD(arg0, u8, 0x9B)++;

        timer_signed = -1;
        if (FIELD(arg3, u32, 0x1C) & 0x228) {
            timer_signed = 8;
        }
        FIELD(arg0, s16, 0x96) = timer_signed;

        x = FIELD(arg1, s32, 0x0C);
        rounded_x = x;
        if (x < 0) {
            rounded_x = x + 3;
        }
        y = FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 0x0C) = x - (rounded_x >> 2);
        rounded_y = y;
        if (y < 0) {
            rounded_y = y + 3;
        }
        FIELD(arg1, s32, 0x10) = y - (rounded_y >> 2);
        return;

    case 1:
        FIELD(arg1, s32, 0x0C) -= ((s16 *)&D_8006CCD8)[direction] << 14;
        FIELD(arg1, s32, 0x10) -= ((s16 *)&D_8006CCE8)[direction] << 14;

        if (FIELD(arg0, s16, 0x96) > 0) {
            FIELD(arg0, u16, 0x96)--;
            goto state1_timer_done;
        }
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            FIELD(arg0, s16, 0x96) = 0;
        }
state1_timer_done:
        if (FIELD(arg0, s16, 0x96) != 0) {
            return;
        }
        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg0, u8, 0x9B) = 0;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_800AAA54(arg0, arg1, arg2, D_80175158);
            return;
        }
        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        FIELD(arg1, s32, 0x14) = 0xFFFE0000;
        if (FIELD(arg0, s16, 0x96) != 0) {
            s32 scaled;
            s32 origin;

            scaled = FIELD(arg2, u8, 0x24) << 6;
            origin = FIELD(arg1, s16, 2);
            origin -= 0x20;
            scaled -= origin;
            scaled <<= 15;
            FIELD(arg1, s32, 0x0C) = scaled >> 1;
            scaled = FIELD(arg2, u8, 0x25) << 6;
            origin = FIELD(arg1, s16, 6);
            origin -= 0x20;
            scaled -= origin;
            scaled <<= 15;
            FIELD(arg1, s32, 0x10) = scaled >> 1;
            FIELD(arg1, s32, 0x0C) += FIELD(arg1, s32, 0x0C) >> 1;
            FIELD(arg1, s32, 0x10) += FIELD(arg1, s32, 0x10) >> 1;
        }

        {
            s16 timer = (u16)FIELD(arg0, s16, 0x96) - 1;

            FIELD(arg0, s16, 0x96) = timer;
            if (timer > 0) {
                return;
            }
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        FIELD(arg3, u32, 0x1C) |= 0x00040000;
        FIELD(arg2, void *, 0x2C) = D_80175148;
        func_80047784(arg2,
            D_80175148[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        {
            u8 *base = (u8 *)&D_80083460;

            if (FIELD(base, s32, 0x10) == (u8 *)arg3 - 0x20) {
                FIELD(base, u32, 0x10) &= 0x7FFFFFFF;
            }
        }
        FIELD(arg0, void *, 0x8C) = D_80171400;
        return;

    default:
        return;
    }
}
