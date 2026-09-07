#include "common.h"

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

typedef struct S_801722BC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801722BC_1;   /* arg3 in func_801722BC */

typedef struct S_801722BC_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801722BC_2;   /* arg2 in func_801722BC */

typedef struct S_801722BC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801722BC_3;   /* arg1 in func_801722BC */

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
            D_801765F0[((D_80083228 + ((S_801722BC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)arg0)->unk_98 |= 8;
        ((S_801722BC_1 *)arg3)->unk_1C &= 0xF7FFFFFF;
        ((S_801722BC_0 *)arg0)->unk_9E.s = 5;
        ((S_801722BC_0 *)arg0)->unk_A0 = 0;
        ((S_801722BC_0 *)arg0)->unk_9B++;
        /* fallthrough */

    case 1:
        ((S_801722BC_0 *)arg0)->unk_90 -= ((S_801722BC_0 *)arg0)->unk_A0;
        count = ((S_801722BC_0 *)arg0)->unk_9E.u;
        if (count != 0) {
            delta = ((S_801722BC_2 *)arg2)->unk_24 << 6;
            position = ((S_801722BC_3 *)arg1)->unk_02;
            position -= 0x20;
            delta -= position;
            ((S_801722BC_3 *)arg1)->unk_0C = (delta << 16) / count;

            position = ((S_801722BC_3 *)arg1)->unk_06;
            delta = ((S_801722BC_2 *)arg2)->unk_25 << 6;
            position -= 0x20;
            delta -= position;
            ((S_801722BC_3 *)arg1)->unk_10 =
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
            ((S_801722BC_1 *)arg3)->unk_1C |= 0x08000000;
            ((S_801722BC_0 *)arg0)->unk_9B++;
        }
        /* fallthrough */

    case 2:
        if (((S_801722BC_1 *)arg3)->unk_1C & 0x08000000) {
            ((S_801722BC_0 *)arg0)->unk_98 &= 0xFFF7;
            ((S_801722BC_3 *)arg1)->unk_14 = 0;
            ((S_801722BC_3 *)arg1)->unk_10 = 0;
            ((S_801722BC_3 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1, ((S_801722BC_2 *)arg2)->unk_24,
                          ((S_801722BC_2 *)arg2)->unk_25);

            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801765F8;
            func_80047784(
                arg2,
                D_801765F8[((D_80083228 + ((S_801722BC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801722BC_0 *)arg0)->unk_9B++;
        }
        break;
    }

    next = ((S_801722BC_0 *)arg0)->unk_96 - 1;
    ((S_801722BC_0 *)arg0)->unk_96 = next;
    if ((s16)next <= 0) {
        ((S_801722BC_3 *)arg1)->unk_14 = 0;
        ((S_801722BC_3 *)arg1)->unk_10 = 0;
        ((S_801722BC_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801722BC_2 *)arg2)->unk_24,
                      ((S_801722BC_2 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        global = &D_80083460;
        if (((S_801722BC_4 *)global)->unk_08.s != 0) {
            ((S_801722BC_4 *)global)->unk_08.u--;
        }

        flags = ((S_801722BC_1 *)arg3)->unk_1C;
        if (flags & 0x2000) {
            if (((S_801722BC_1 *)arg3)->unk_46 & 0x8000) {
                ((S_801722BC_1 *)arg3)->unk_46 &= 0x7FFF;
            }
        } else if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                ((S_801722BC_1 *)arg3)->unk_2A =
                    func_800A0818(((S_801722BC_2 *)arg2)->unk_24,
                                   ((S_801722BC_2 *)arg2)->unk_25,
                                   D_80082E80[0x24], D_80082E80[0x25], &sp18);
            }
        }

        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_801722BC_0 *)arg0)->unk_8C = D_80170EE4;
            func_800A9A04(arg3);
        }
    }
}
