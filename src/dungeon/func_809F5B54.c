#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


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

    direction = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;

    switch (((S_80173354_1 *)arg0)->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
            func_800AAA54(arg0, arg1, arg2, D_80175158);
            return;
        }

        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173354_1 *)arg0)->unk_96.s = 0;
            ((S_80173354_1 *)arg0)->unk_9B = 2;
            return;
        }

        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((s16 *)&D_8006CCD8)[direction] << 18;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = ((s16 *)&D_8006CCE8)[direction] << 18;
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0x40000;
        ((S_80173354_1 *)arg0)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xF7FFFFFF;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xFFFBFFFF;
        ((S_80173354_1 *)arg0)->unk_9B++;

        timer_signed = -1;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x228) {
            timer_signed = 8;
        }
        ((S_80173354_1 *)arg0)->unk_96.s = timer_signed;

        x = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32;
        rounded_x = x;
        if (x < 0) {
            rounded_x = x + 3;
        }
        y = ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = x - (rounded_x >> 2);
        rounded_y = y;
        if (y < 0) {
            rounded_y = y + 3;
        }
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = y - (rounded_y >> 2);
        return;

    case 1:
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -= ((s16 *)&D_8006CCD8)[direction] << 14;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -= ((s16 *)&D_8006CCE8)[direction] << 14;

        if (((S_80173354_1 *)arg0)->unk_96.s > 0) {
            ((S_80173354_1 *)arg0)->unk_96.u--;
            goto state1_timer_done;
        }
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
            ((S_80173354_1 *)arg0)->unk_96.s = 0;
        }
state1_timer_done:
        if (((S_80173354_1 *)arg0)->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            ((S_80173354_1 *)arg0)->unk_9B = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
            func_800AAA54(arg0, arg1, arg2, D_80175158);
            return;
        }
        ((S_80173354_1 *)arg0)->unk_96.s = 8;
        ((S_80173354_1 *)arg0)->unk_9B++;
        return;

    case 2:
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0xFFFE0000;
        if (((S_80173354_1 *)arg0)->unk_96.s != 0) {
            s32 scaled;
            s32 origin;

            scaled = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
            origin = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
            origin -= 0x20;
            scaled -= origin;
            scaled <<= 15;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = scaled >> 1;
            scaled = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
            origin = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
            origin -= 0x20;
            scaled -= origin;
            scaled <<= 15;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = scaled >> 1;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 += ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 >> 1;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v += ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v >> 1;
        }

        {
            s16 timer = (u16)((S_80173354_1 *)arg0)->unk_96.s - 1;

            ((S_80173354_1 *)arg0)->unk_96.s = timer;
            if (timer > 0) {
                return;
            }
        }

        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

        ((S_80173354_1 *)arg0)->unk_90 = 0;
        ((S_80173354_1 *)arg0)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x08000000;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x00040000;
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80175148;
        func_80047784(arg2,
            D_80175148[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
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
