#include "common.h"


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


typedef struct S_80172DDC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_80172DDC_0;   /* arg0 in func_80172DDC */

typedef struct S_80172DDC_1 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172DDC_1;   /* arg2 in func_80172DDC */

typedef struct S_80172DDC_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172DDC_2;   /* arg3 in func_80172DDC */

typedef struct S_80172DDC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172DDC_3;   /* arg1 in func_80172DDC */

void func_80172DDC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = ((S_80172DDC_0 *)arg0)->unk_9B;
    if ((u32)state >= 6) {
        return;
    }
    (void)keepalive;
    goto *D_80170868[state];

L0:
    if (!(((S_80172DDC_1 *)arg2)->unk_14 & 0x8000)) {
        func_800A56E0(0x80E);
    }
    ((S_80172DDC_0 *)arg0)->unk_9B++;

L1:
    if (((S_80172DDC_1 *)arg2)->unk_14 & 0x8000) {
        ((S_80172DDC_0 *)arg0)->unk_96.u = 0x100;
        ((S_80172DDC_0 *)arg0)->unk_9B = 5;
        func_8009C12C(arg3, arg2, ((S_80172DDC_2 *)arg3)->unk_2A, 1);
        func_80173264();
    }

    ((S_80172DDC_1 *)arg2)->unk_05 -= 2;
    {
        u32 index = ((u16)((S_80172DDC_2 *)arg3)->unk_2A >> 8) & 0xE;
        ((S_80172DDC_3 *)arg1)->unk_0C -=
            (s32)*(s16 *)((u8 *)&D_8006CCD8 + index) << 16;
        ((S_80172DDC_3 *)arg1)->unk_10 -=
            (s32)*(s16 *)((u8 *)&D_8006CCE8 + index) << 16;
    }
    if (((S_80172DDC_1 *)arg2)->unk_14 & 0x6000) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175E78;
        func_80047784(
            arg2,
            D_80175E78[((D_80083228 + ((S_80172DDC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172DDC_0 *)arg0)->unk_9B++;
    }

L2:
    {
        u16 timer = ((S_80172DDC_0 *)arg0)->unk_A0.at02.v + 0x10;

        ((S_80172DDC_0 *)arg0)->unk_A0.at02.v = timer;
        if ((s16)timer >= 0x31) {
            ((S_80172DDC_0 *)arg0)->unk_A0.at02.v = 0x30;
            ((S_80172DDC_3 *)arg1)->unk_10 = 0;
            ((S_80172DDC_3 *)arg1)->unk_0C = 0;
        }
    }
    if (!(((S_80172DDC_1 *)arg2)->unk_14 & 0x6000)) {
        return;
    }
    ((S_80172DDC_3 *)arg1)->unk_14 = 0;
    ((S_80172DDC_3 *)arg1)->unk_10 = 0;
    ((S_80172DDC_3 *)arg1)->unk_0C = 0;
    if (((S_80172DDC_0 *)arg0)->unk_A0.at02u.v < 0x30) {
        return;
    }
    {
        s32 current_state = ((S_80172DDC_0 *)arg0)->unk_9B;

        ((S_80172DDC_0 *)arg0)->unk_96.u = 0;
        if (current_state == 0) {
            return;
        }
    }
    func_800A56E0(0x808);
    ((S_80172DDC_0 *)arg0)->unk_9B++;
    func_80174DA0((u8 *)arg0 - 0x20, (u8 *)arg3 + 0x2A,
                  (u8 *)arg0 + 0x9B);
    func_80173264();

L3:
    {
        u8 *table_x = (u8 *)&D_8006CCD8;
        u8 *table_y = (u8 *)&D_8006CCE8;
        u16 timer;

        ((S_80172DDC_3 *)arg1)->unk_0C +=
            (s32)*(s16 *)(table_x +
                (((u16)((S_80172DDC_2 *)arg3)->unk_2A >> 8) & 0xE)) << 17;

        ((S_80172DDC_3 *)arg1)->unk_10 +=
            (s32)*(s16 *)(table_y +
                (((u16)((S_80172DDC_2 *)arg3)->unk_2A >> 8) & 0xE)) << 17;

        ((S_80172DDC_0 *)arg0)->unk_A0.at00.v -= (s32)((S_80172DDC_0 *)arg0)->unk_96.s << 17;
        timer = ((S_80172DDC_0 *)arg0)->unk_96.u + 1;
        ((S_80172DDC_0 *)arg0)->unk_96.u = timer;
        if ((s16)timer < 9) {
            return;
        }

        func_8009C12C(arg3, arg2, ((S_80172DDC_2 *)arg3)->unk_2A, 1);
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175E80;
        func_80047784(
            arg2,
            D_80175E80[((D_80083228 + ((S_80172DDC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);

        ((S_80172DDC_3 *)arg1)->unk_0C =
            -*(s16 *)(table_x +
                (((u16)((S_80172DDC_2 *)arg3)->unk_2A >> 8) & 0xE)) << 20;

        ((S_80172DDC_3 *)arg1)->unk_10 =
            -*(s16 *)(table_y +
                (((u16)((S_80172DDC_2 *)arg3)->unk_2A >> 8) & 0xE)) << 20;
        ((S_80172DDC_0 *)arg0)->unk_A8 = ((S_80172DDC_3 *)arg1)->unk_0C / 6;
        ((S_80172DDC_0 *)arg0)->unk_AC = ((S_80172DDC_3 *)arg1)->unk_10 / 6;
        ((S_80172DDC_0 *)arg0)->unk_96.u = 0;
        ((S_80172DDC_0 *)arg0)->unk_9B++;
        func_80173264();
    }

L4:
    ((S_80172DDC_3 *)arg1)->unk_0C -= ((S_80172DDC_0 *)arg0)->unk_A8;
    ((S_80172DDC_3 *)arg1)->unk_10 -= ((S_80172DDC_0 *)arg0)->unk_AC;
    ((S_80172DDC_0 *)arg0)->unk_A0.at00.v =
        func_800644B8(((S_80172DDC_0 *)arg0)->unk_96.s * 146) * 160 + 0x100000;

L5:
    {
        u16 timer = ((S_80172DDC_0 *)arg0)->unk_96.u + 1;

        ((S_80172DDC_0 *)arg0)->unk_96.u = timer;
        if ((s16)timer < 7 && !(((S_80172DDC_1 *)arg2)->unk_14 & 0x8000)) {
            return;
        }
    }
    ((S_80172DDC_3 *)arg1)->unk_14 = 0;
    ((S_80172DDC_3 *)arg1)->unk_10 = 0;
    ((S_80172DDC_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172DDC_1 *)arg2)->unk_24, ((S_80172DDC_1 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_80172DDC_0 *)arg0)->unk_8C = D_801710EC;
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg3 + (0x46))) &= 0x7FFF;
    ((S_80172DDC_0 *)arg0)->unk_98 &= 0xFFF7;
    func_800A4ACC(arg3);
}

/* MECHANISM: The four live args naturally select the retail 0x30 frame and s0-s3,
   while the L3 table bases remain held in s4/s5 across calls.
   Storing both X/Y numerators before their /6 writes exposes the multiply-latency schedule;
   zeroing the timer before incrementing state places retail's final sh before sb. */
