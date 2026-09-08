#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8017586C(void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_80170860[6];
extern u8 D_80171FA4[9];
extern u8 D_80175C68[8];
extern u8 D_80175C70[8];


typedef struct S_80173930_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_80173930_0;   /* arg0 in func_80173930 */




void func_80173930(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = ((S_80173930_0 *)arg0)->unk_9B;
    if ((u32)state >= 6) {
        return;
    }
    (void)keepalive;
    goto *D_80170860[state];

L0:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_800A56E0(0x80E);
    }
    ((S_80173930_0 *)arg0)->unk_9B++;

L1:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80173930_0 *)arg0)->unk_96.u = 0x100;
        ((S_80173930_0 *)arg0)->unk_9B = 5;
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        return;
    }

    ((Rec_D_80082E80 *)arg2)->unk_05.as_u8 -= 2;
    {
        u32 index = ((u16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -=
            (s32)*(s16 *)((u8 *)&D_8006CCD8 + index) << 16;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -=
            (s32)*(s16 *)((u8 *)&D_8006CCE8 + index) << 16;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175C68;
        func_80047784(
            arg2,
            D_80175C68[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_80173930_0 *)arg0)->unk_9B++;
    }

L2:
    {
        u16 timer = ((S_80173930_0 *)arg0)->unk_A0.at02.v + 0x10;

        ((S_80173930_0 *)arg0)->unk_A0.at02.v = timer;
        if ((s16)timer >= 0x31) {
            ((S_80173930_0 *)arg0)->unk_A0.at02.v = 0x30;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        }
    }
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        return;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    if (((S_80173930_0 *)arg0)->unk_A0.at02u.v < 0x30) {
        return;
    }
    {
        s32 current_state = ((S_80173930_0 *)arg0)->unk_9B;

        ((S_80173930_0 *)arg0)->unk_96.u = 0;
        if (current_state == 0) {
            return;
        }
    }
    func_800A56E0(0x808);
    ((S_80173930_0 *)arg0)->unk_9B++;
    func_8017586C((u8 *)arg0 - 0x20, (u8 *)arg3 + 0x2A,
                  (u8 *)arg0 + 0x9B);
    return;

L3:
    {
        u8 *table_x = (u8 *)&D_8006CCD8;
        u8 *table_y = (u8 *)&D_8006CCE8;
        u16 timer;

        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 +=
            (s32)*(s16 *)(table_x +
                (((u16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE)) << 17;

        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v +=
            (s32)*(s16 *)(table_y +
                (((u16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE)) << 17;

        ((S_80173930_0 *)arg0)->unk_A0.at00.v -= (s32)((S_80173930_0 *)arg0)->unk_96.s << 17;
        timer = ((S_80173930_0 *)arg0)->unk_96.u + 1;
        ((S_80173930_0 *)arg0)->unk_96.u = timer;
        if ((s16)timer < 9) {
            return;
        }

        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175C70;
        func_80047784(
            arg2,
            D_80175C70[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 =
            -*(s16 *)(table_x +
                (((u16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE)) << 20;

        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            -*(s16 *)(table_y +
                (((u16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE)) << 20;
        ((S_80173930_0 *)arg0)->unk_A8 = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 / 6;
        ((S_80173930_0 *)arg0)->unk_AC = ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v / 6;
        ((S_80173930_0 *)arg0)->unk_96.u = 0;
        ((S_80173930_0 *)arg0)->unk_9B++;
        return;
    }

L4:
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -= ((S_80173930_0 *)arg0)->unk_A8;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -= ((S_80173930_0 *)arg0)->unk_AC;
    ((S_80173930_0 *)arg0)->unk_A0.at00.v =
        func_800644B8(((S_80173930_0 *)arg0)->unk_96.s * 146) * 160 + 0x100000;

L5:
    {
        u16 timer = ((S_80173930_0 *)arg0)->unk_96.u + 1;

        ((S_80173930_0 *)arg0)->unk_96.u = timer;
        if ((s16)timer < 7 && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_80173930_0 *)arg0)->unk_8C = D_80171FA4;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
}

/* MECHANISM: The four live args naturally select the retail 0x30 frame and s0-s3,
   while the L3 table bases remain held in s4/s5 across calls.
   Storing both X/Y numerators before their /6 writes exposes the multiply-latency schedule;
   zeroing the timer before incrementing state places retail's final sh before sb. */
