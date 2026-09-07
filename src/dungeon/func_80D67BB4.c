#include "common.h"

typedef struct S_801733B4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
    u8 pad_A8[0x2];
    union { u16 s; s16 u; } unk_AA;   /* accessed as both */
} S_801733B4_0;   /* arg0 in func_801733B4 */

typedef struct S_801733B4_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801733B4_1;   /* arg3 in func_801733B4 */

typedef struct S_801733B4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801733B4_2;   /* arg1 in func_801733B4 */

typedef struct S_801733B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801733B4_3;   /* arg2 in func_801733B4 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2348[];
extern u8 D_800E2368[];
extern u8 D_800E2370[];
extern s32 D_80171F1C;

void func_801733B4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s32 delta;
    u16 next;
    s32 state;

    state = ((S_801733B4_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto update_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto update_timer;

state_zero:
    next = ((S_801733B4_0 *)arg0)->unk_AA.s + 1;
    ((S_801733B4_0 *)arg0)->unk_AA.s = next;
    if ((s16)next < 2) {
        goto update_timer;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E2368;
    func_80047784(arg2,
        D_800E2368[((D_80083228 + ((S_801733B4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801733B4_0 *)arg0)->unk_98 |= 8;
    ((S_801733B4_1 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
    ((S_801733B4_0 *)arg0)->unk_AA.s = 5;
    ((S_801733B4_0 *)arg0)->unk_A4 = 0;
    ((S_801733B4_0 *)arg0)->unk_9B++;

state_one:
    ((S_801733B4_0 *)arg0)->unk_90.at00.v -= ((S_801733B4_0 *)arg0)->unk_A4;
    if (((S_801733B4_0 *)arg0)->unk_AA.u != 0) {
        ((S_801733B4_2 *)arg1)->unk_0C =
            (((((S_801733B4_3 *)arg2)->unk_24 << 6) -
              ({ ((S_801733B4_2 *)arg1)->unk_02 - 0x20; })) << 16) /
            ((S_801733B4_0 *)arg0)->unk_AA.u;
        delta = ((S_801733B4_2 *)arg1)->unk_06 - 0x20;
        ((S_801733B4_2 *)arg1)->unk_10 =
            (((((S_801733B4_3 *)arg2)->unk_25 << 6) - delta) << 16) /
            ((S_801733B4_0 *)arg0)->unk_AA.u;
        ((S_801733B4_0 *)arg0)->unk_A4 =
            (-func_800644B8(((S_801733B4_0 *)arg0)->unk_AA.u * 0x199)) << 10;
    }
    ((S_801733B4_0 *)arg0)->unk_90.at00.v += ((S_801733B4_0 *)arg0)->unk_A4;
    next = ((S_801733B4_0 *)arg0)->unk_AA.s - 1;
    ((S_801733B4_0 *)arg0)->unk_AA.s = next;
    if ((s16)next < 0) {
        ((S_801733B4_0 *)arg0)->unk_90.at02.v = -0x10;
        ((S_801733B4_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801733B4_1 *)arg3)->unk_1C.s |= 0x08000000;
        ((S_801733B4_0 *)arg0)->unk_9B++;
    }

state_two:
    if (((S_801733B4_1 *)arg3)->unk_1C.s & 0x08000000) {
        ((S_801733B4_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801733B4_2 *)arg1)->unk_14 = 0;
        ((S_801733B4_2 *)arg1)->unk_10 = 0;
        ((S_801733B4_2 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801733B4_3 *)arg2)->unk_24, ((S_801733B4_3 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E2370;
        func_80047784(arg2,
            D_800E2370[((D_80083228 + ((S_801733B4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801733B4_0 *)arg0)->unk_9B++;
        goto update_timer;
    }
    goto update_timer;

state_three:
    if (((S_801733B4_3 *)arg2)->unk_2C != D_800E2348) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E2348;
        func_80047784(arg2,
            D_800E2348[((D_80083228 + ((S_801733B4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801733B4_0 *)arg0)->unk_9E = 0;
    }

update_timer:
    next = ((S_801733B4_0 *)arg0)->unk_96 - 1;
    ((S_801733B4_0 *)arg0)->unk_96 = next;
    if (((s32)next << 16) <= 0) {
        s32 flags;
        s16 *counter;

        ((S_801733B4_2 *)arg1)->unk_14 = 0;
        ((S_801733B4_2 *)arg1)->unk_10 = 0;
        ((S_801733B4_2 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801733B4_3 *)arg2)->unk_24, ((S_801733B4_3 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        counter = (s16 *)&D_80083460;
        if (counter[4] != 0) {
            ((u16 *)counter)[4]--;
        }
        flags = ((S_801733B4_1 *)arg3)->unk_1C.u;
        if (flags & 0x2000) {
            if (((S_801733B4_1 *)arg3)->unk_46 & 0x8000) {
                ((S_801733B4_1 *)arg3)->unk_46 &= 0x7FFF;
                goto check_actor;
            }
        } else {
            if (flags & 0x410) {
                goto check_actor;
            }
            if (!(flags & 0x20000)) {
                goto check_actor;
            }
            ((S_801733B4_1 *)arg3)->unk_2A = func_800A0818(
                ((S_801733B4_3 *)arg2)->unk_24, ((S_801733B4_3 *)arg2)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &scratch);
        }

check_actor:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_801733B4_0 *)arg0)->unk_8C = &D_80171F1C;
            func_800A9A04(arg3);
        }
    }
}
