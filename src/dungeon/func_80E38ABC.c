#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801722BC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801722BC_0;   /* arg0 in func_801722BC */




typedef struct S_801722BC_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_801722BC_4;   /* global in func_801722BC */



extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170EE4[];
extern u8 D_801765F0[];
extern u8 D_801765F8[];

void func_801722BC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s16 count;
    u16 next;
    u8 state;
    s32 flags;
    s32 delta;
    s32 position;
    s32 *global;

    state = ((S_801722BC_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        next = ((S_801722BC_0 *)arg0)->unk_9E.s - 1;
        ((S_801722BC_0 *)arg0)->unk_9E.s = next;
        if ((s16)next > 0) {
            break;
        }

        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801765F0;
        func_80047784(
            arg2,
            D_801765F0[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)arg0)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= 0xF7FFFFFF;
        ((S_801722BC_0 *)arg0)->unk_9E.s = 5;
        ((S_801722BC_0 *)arg0)->unk_A0 = 0;
        ((S_801722BC_0 *)arg0)->unk_9B++;
        /* fallthrough */

    case 1:
        ((S_801722BC_0 *)arg0)->unk_90 -= ((S_801722BC_0 *)arg0)->unk_A0;
        count = ((S_801722BC_0 *)arg0)->unk_9E.u;
        if (count != 0) {
            delta = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
            position = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
            position -= 0x20;
            delta -= position;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (delta << 16) / count;

            position = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
            delta = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
            position -= 0x20;
            delta -= position;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
                (delta << 16) / ((S_801722BC_0 *)arg0)->unk_9E.u;
            ((S_801722BC_0 *)arg0)->unk_A0 =
                (-func_800644B8(((S_801722BC_0 *)arg0)->unk_9E.u * 0x199)) << 9;
        }

        ((S_801722BC_0 *)arg0)->unk_90 += ((S_801722BC_0 *)arg0)->unk_A0;
        next = ((S_801722BC_0 *)arg0)->unk_9E.s - 1;
        ((S_801722BC_0 *)arg0)->unk_9E.s = next;
        if ((s16)next < 0) {
            ((S_801722BC_0 *)arg0)->unk_90 = 0;
            ((S_801722BC_0 *)arg0)->unk_98 &= 0xFFF7;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 |= 0x08000000;
            ((S_801722BC_0 *)arg0)->unk_9B++;
        }
        /* fallthrough */

    case 2:
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x08000000) {
            ((S_801722BC_0 *)arg0)->unk_98 &= 0xFFF7;
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
            func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24,
                          ((Rec_D_80082E80 *)arg2)->unk_25);

            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801765F8;
            func_80047784(
                arg2,
                D_801765F8[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_801722BC_0 *)arg0)->unk_9B++;
        }
        break;
    }

    next = ((S_801722BC_0 *)arg0)->unk_96 - 1;
    ((S_801722BC_0 *)arg0)->unk_96 = next;
    if ((s16)next <= 0) {
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24,
                      ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        global = &D_80083460;
        if (((S_801722BC_4 *)global)->unk_08.s != 0) {
            ((S_801722BC_4 *)global)->unk_08.u--;
        }

        flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
        if (flags & 0x2000) {
            if (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) {
                ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
            }
        } else if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 =
                    func_800A0818(((Rec_D_80082E80 *)arg2)->unk_24,
                                   ((Rec_D_80082E80 *)arg2)->unk_25,
                                   D_80082E80[0x24], D_80082E80[0x25], &sp18);
            }
        }

        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_801722BC_0 *)arg0)->unk_8C = D_80170EE4;
            func_800A9A04(arg3);
        }
    }
}
