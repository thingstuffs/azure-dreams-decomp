#include "common.h"

typedef struct S_801721B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801721B0_0;   /* arg0 in func_801721B0 */

typedef struct S_801721B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801721B0_1;   /* arg2 in func_801721B0 */

typedef struct S_801721B0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801721B0_2;   /* arg3 in func_801721B0 */

typedef struct S_801721B0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801721B0_3;   /* arg1 in func_801721B0 */

typedef struct S_801721B0_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_801721B0_4;   /* global in func_801721B0 */



extern void func_80047784(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A5DFC(void *, void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170F20[];
extern u8 D_801762D8[];
extern u8 D_801762E0[];

void func_801721B0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 temp_delta;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v0;
    s32 temp_v1;
    u8 *global;

    temp_v1 = ((S_801721B0_0 *)arg0)->unk_9B;
    if (temp_v1 == 1) {
        goto state_one;
    }
    if (temp_v1 >= 2) {
        goto check_state_two;
    }
    if (temp_v1 == 0) {
        goto state_zero;
    }
    goto common_update;

check_state_two:
    if (temp_v1 == 2) {
        goto state_two;
    }
    goto common_update;

state_zero:
    if (((S_801721B0_1 *)arg2)->unk_14 & 0x6000) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_801762D8;
        func_80047784(
            arg2,
            D_801762D8[((D_80083228 + ((S_801721B0_2 *)arg3)->unk_2A + 0x100) >>
                         9) &
                        7],
            0);
        ((S_801721B0_0 *)arg0)->unk_98 |= 8;
        ((S_801721B0_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
        ((S_801721B0_0 *)arg0)->unk_9E.s = 5;
        ((S_801721B0_0 *)arg0)->unk_A0 = 0;
        ((S_801721B0_0 *)arg0)->unk_9B++;
        goto state_one;
    }
    goto common_update;

state_one:
    temp_a0 = ((S_801721B0_0 *)arg0)->unk_9E.s;
    ((S_801721B0_0 *)arg0)->unk_90 =
        ((S_801721B0_0 *)arg0)->unk_90 - ((S_801721B0_0 *)arg0)->unk_A0;
    if (temp_a0 != 0) {
        ((S_801721B0_3 *)arg1)->unk_0C =
            (((((S_801721B0_1 *)arg2)->unk_24 << 6) -
              ({ ((S_801721B0_3 *)arg1)->unk_02 - 0x20; })) <<
             0x10) /
            temp_a0;
        ((S_801721B0_3 *)arg1)->unk_10 =
            (((((S_801721B0_1 *)arg2)->unk_25 << 6) -
              (temp_delta = ((S_801721B0_3 *)arg1)->unk_06 - 0x20)) <<
             0x10) /
            ((S_801721B0_0 *)arg0)->unk_9E.s;
        ((S_801721B0_0 *)arg0)->unk_A0 =
            (-func_800644B8(((S_801721B0_0 *)arg0)->unk_9E.s * 0x199)) << 9;
    }
    ((S_801721B0_0 *)arg0)->unk_90 =
        ((S_801721B0_0 *)arg0)->unk_90 + ((S_801721B0_0 *)arg0)->unk_A0;
    temp_v1_2 = ((S_801721B0_0 *)arg0)->unk_9E.u - 1;
    ((S_801721B0_0 *)arg0)->unk_9E.s = temp_v1_2;
    if ((s16)temp_v1_2 < 0) {
        ((S_801721B0_0 *)arg0)->unk_90 = 0;
        ((S_801721B0_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801721B0_2 *)arg3)->unk_1C |= 0x08000000;
        ((S_801721B0_0 *)arg0)->unk_9B++;
    }

state_two:
    if (((S_801721B0_2 *)arg3)->unk_1C & 0x08000000) {
        ((S_801721B0_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801721B0_3 *)arg1)->unk_14 = 0;
        ((S_801721B0_3 *)arg1)->unk_10 = 0;
        ((S_801721B0_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801721B0_1 *)arg2)->unk_24,
                     ((S_801721B0_1 *)arg2)->unk_25);
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_801762E0;
        func_80047784(
            arg2,
            D_801762E0[((D_80083228 + ((S_801721B0_2 *)arg3)->unk_2A + 0x100) >>
                         9) &
                        7],
            0);
        ((S_801721B0_0 *)arg0)->unk_9B++;
    }

common_update:
    temp_v0 = ((S_801721B0_0 *)arg0)->unk_96 - 1;
    ((S_801721B0_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_801721B0_3 *)arg1)->unk_14 = 0;
        ((S_801721B0_3 *)arg1)->unk_10 = 0;
        ((S_801721B0_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801721B0_1 *)arg2)->unk_24,
                     ((S_801721B0_1 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        global = (u8 *)&D_80083460;
        if (((S_801721B0_4 *)global)->unk_08 != 0) {
            ((S_801721B0_4 *)global)->unk_08 = (u16)((S_801721B0_4 *)global)->unk_08 - 1;
        }
        temp_v1_3 = ((S_801721B0_2 *)arg3)->unk_1C;
        if (temp_v1_3 & 0x2000) {
            u16 temp_flags;

            temp_flags = ((S_801721B0_2 *)arg3)->unk_46;
            if (temp_flags & 0x8000) {
                ((S_801721B0_2 *)arg3)->unk_46 = temp_flags & 0x7FFF;
            }
            goto coordinate_done;
        }
        if (temp_v1_3 & 0x410) {
            goto coordinate_done;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto coordinate_done;
        }
        ((S_801721B0_2 *)arg3)->unk_2A = func_800A0818(
            ((S_801721B0_1 *)arg2)->unk_24, ((S_801721B0_1 *)arg2)->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);

coordinate_done:
        func_800A5DFC(arg3, arg1);
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            ((S_801721B0_0 *)arg0)->unk_8C = D_80170F20;
            func_800A9A04(arg3);
        }
    }
}
