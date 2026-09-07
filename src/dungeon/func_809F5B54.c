#include "common.h"

typedef struct S_80173354_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_80173354_0;   /* arg3 in func_80173354 */

typedef struct S_80173354_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173354_1;   /* arg0 in func_80173354 */

typedef struct S_80173354_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173354_2;   /* arg1 in func_80173354 */

typedef struct S_80173354_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173354_3;   /* arg2 in func_80173354 */

typedef struct S_80173354_4 {
    u8 pad_00[0x10];
    union { s32 s; u32 u; } unk_10;   /* accessed as both */
} S_80173354_4;   /* base in func_80173354 */



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

    direction = (((S_80173354_0 *)arg3)->unk_6A >> 9) & 7;

    switch (((S_80173354_1 *)arg0)->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        if (((S_80173354_0 *)arg3)->unk_28 == 0) {
            ((S_80173354_2 *)arg1)->unk_14 = 0;
            ((S_80173354_2 *)arg1)->unk_10 = 0;
            ((S_80173354_2 *)arg1)->unk_0C = 0;
            func_800AAA54(arg0, arg1, arg2, D_80175158);
            return;
        }

        if (((S_80173354_3 *)arg2)->unk_14 & 0x8000) {
            ((S_80173354_1 *)arg0)->unk_96.s = 0;
            ((S_80173354_1 *)arg0)->unk_9B = 2;
            return;
        }

        ((S_80173354_2 *)arg1)->unk_0C = ((s16 *)&D_8006CCD8)[direction] << 18;
        ((S_80173354_2 *)arg1)->unk_10 = ((s16 *)&D_8006CCE8)[direction] << 18;
        ((S_80173354_2 *)arg1)->unk_14 = 0x40000;
        ((S_80173354_1 *)arg0)->unk_98 |= 8;
        ((S_80173354_0 *)arg3)->unk_1C &= 0xF7FFFFFF;
        ((S_80173354_0 *)arg3)->unk_1C &= 0xFFFBFFFF;
        ((S_80173354_1 *)arg0)->unk_9B++;

        timer_signed = -1;
        if (((S_80173354_0 *)arg3)->unk_1C & 0x228) {
            timer_signed = 8;
        }
        ((S_80173354_1 *)arg0)->unk_96.s = timer_signed;

        x = ((S_80173354_2 *)arg1)->unk_0C;
        rounded_x = x;
        if (x < 0) {
            rounded_x = x + 3;
        }
        y = ((S_80173354_2 *)arg1)->unk_10;
        ((S_80173354_2 *)arg1)->unk_0C = x - (rounded_x >> 2);
        rounded_y = y;
        if (y < 0) {
            rounded_y = y + 3;
        }
        ((S_80173354_2 *)arg1)->unk_10 = y - (rounded_y >> 2);
        return;

    case 1:
        ((S_80173354_2 *)arg1)->unk_0C -= ((s16 *)&D_8006CCD8)[direction] << 14;
        ((S_80173354_2 *)arg1)->unk_10 -= ((s16 *)&D_8006CCE8)[direction] << 14;

        if (((S_80173354_1 *)arg0)->unk_96.s > 0) {
            ((S_80173354_1 *)arg0)->unk_96.u--;
            goto state1_timer_done;
        }
        if (((S_80173354_3 *)arg2)->unk_14 & 0x6000) {
            ((S_80173354_1 *)arg0)->unk_96.s = 0;
        }
state1_timer_done:
        if (((S_80173354_1 *)arg0)->unk_96.s != 0) {
            return;
        }
        if (((S_80173354_0 *)arg3)->unk_28 == 0) {
            ((S_80173354_1 *)arg0)->unk_9B = 0;
            ((S_80173354_2 *)arg1)->unk_14 = 0;
            ((S_80173354_2 *)arg1)->unk_10 = 0;
            ((S_80173354_2 *)arg1)->unk_0C = 0;
            func_800AAA54(arg0, arg1, arg2, D_80175158);
            return;
        }
        ((S_80173354_1 *)arg0)->unk_96.s = 8;
        ((S_80173354_1 *)arg0)->unk_9B++;
        return;

    case 2:
        ((S_80173354_2 *)arg1)->unk_14 = 0xFFFE0000;
        if (((S_80173354_1 *)arg0)->unk_96.s != 0) {
            s32 scaled;
            s32 origin;

            scaled = ((S_80173354_3 *)arg2)->unk_24 << 6;
            origin = ((S_80173354_2 *)arg1)->unk_02;
            origin -= 0x20;
            scaled -= origin;
            scaled <<= 15;
            ((S_80173354_2 *)arg1)->unk_0C = scaled >> 1;
            scaled = ((S_80173354_3 *)arg2)->unk_25 << 6;
            origin = ((S_80173354_2 *)arg1)->unk_06;
            origin -= 0x20;
            scaled -= origin;
            scaled <<= 15;
            ((S_80173354_2 *)arg1)->unk_10 = scaled >> 1;
            ((S_80173354_2 *)arg1)->unk_0C += ((S_80173354_2 *)arg1)->unk_0C >> 1;
            ((S_80173354_2 *)arg1)->unk_10 += ((S_80173354_2 *)arg1)->unk_10 >> 1;
        }

        {
            s16 timer = (u16)((S_80173354_1 *)arg0)->unk_96.s - 1;

            ((S_80173354_1 *)arg0)->unk_96.s = timer;
            if (timer > 0) {
                return;
            }
        }

        ((S_80173354_2 *)arg1)->unk_14 = 0;
        ((S_80173354_2 *)arg1)->unk_10 = 0;
        ((S_80173354_2 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80173354_3 *)arg2)->unk_24, ((S_80173354_3 *)arg2)->unk_25);

        ((S_80173354_1 *)arg0)->unk_90 = 0;
        ((S_80173354_1 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80173354_0 *)arg3)->unk_1C |= 0x08000000;
        ((S_80173354_0 *)arg3)->unk_1C |= 0x00040000;
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80175148;
        func_80047784(arg2,
            D_80175148[((D_80083228 + ((S_80173354_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);

        {
            u8 *base = (u8 *)&D_80083460;

            if (((S_80173354_4 *)base)->unk_10.s == (u8 *)arg3 - 0x20) {
                ((S_80173354_4 *)base)->unk_10.u &= 0x7FFFFFFF;
            }
        }
        ((S_80173354_1 *)arg0)->unk_8C = D_80171400;
        return;

    default:
        return;
    }
}
