#include "common.h"

typedef struct S_80172158_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
} S_80172158_0;   /* arg0 in func_80172158 */

typedef struct S_80172158_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172158_1;   /* arg2 in func_80172158 */

typedef struct S_80172158_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172158_2;   /* arg3 in func_80172158 */

typedef struct S_80172158_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172158_3;   /* arg1 in func_80172158 */

typedef struct S_80172158_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172158_4;   /* counter_base in func_80172158 */



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
extern u8 D_80170E9C[];
extern u8 D_80174EE0[];

void func_80172158(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 temp_a0;
    s32 temp_axis;
    s32 temp_delta;
    s32 temp_position;
    s16 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v0;
    s32 temp_v1;
    u8 *counter_base;

    temp_v1 = ((S_80172158_0 *)arg0)->unk_9B;
    if (temp_v1 == 1) {
        goto block_12;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        goto block_18;
    }
    if (temp_v1 == 2) {
        goto block_16;
    }
    goto block_18;

state_0:
    if (((((S_80172158_1 *)arg2)->unk_04 == 1) &&
         (((S_80172158_1 *)arg2)->unk_14 & 0x1000)) ||
        (((S_80172158_1 *)arg2)->unk_14 & 0xE000)) {
        ((S_80172158_0 *)arg0)->unk_98 |= 8;
        ((S_80172158_2 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
        ((S_80172158_0 *)arg0)->unk_9E = 6;
        ((S_80172158_0 *)arg0)->unk_A0 = 0;
        ((S_80172158_0 *)arg0)->unk_9B++;
        goto block_12;
    }
    goto block_18;

block_12:
    temp_a0 = ((S_80172158_0 *)arg0)->unk_9E;
    ((S_80172158_0 *)arg0)->unk_90 =
        ((S_80172158_0 *)arg0)->unk_90 - ((S_80172158_0 *)arg0)->unk_A0;
    if (temp_a0 != 0) {
        temp_axis = ((S_80172158_1 *)arg2)->unk_24;
        temp_delta = ((S_80172158_3 *)arg1)->unk_02;
        temp_axis <<= 6;
        temp_delta -= 0x20;
        temp_axis -= temp_delta;
        temp_axis <<= 16;
        ((S_80172158_3 *)arg1)->unk_0C = temp_axis / temp_a0;
        temp_delta = ((S_80172158_3 *)arg1)->unk_06 - 0x20;
        ((S_80172158_3 *)arg1)->unk_10 =
            (((((S_80172158_1 *)arg2)->unk_25 << 6) - temp_delta) << 16) /
            (s16)((S_80172158_0 *)arg0)->unk_9E;
        ((S_80172158_0 *)arg0)->unk_A0 =
            (-func_800644B8(((S_80172158_0 *)arg0)->unk_9E * 0x155)) << 9;
    }
    ((S_80172158_0 *)arg0)->unk_90 += ((S_80172158_0 *)arg0)->unk_A0;
    temp_v1_2 = --((S_80172158_0 *)arg0)->unk_9E;
    if (temp_v1_2 < 0) {
        ((S_80172158_0 *)arg0)->unk_90 = 0;
        ((S_80172158_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172158_2 *)arg3)->unk_1C.s |= 0x08000000;
        ((S_80172158_0 *)arg0)->unk_9B++;
    }

block_16:
    if (((S_80172158_2 *)arg3)->unk_1C.s & 0x08000000) {
        ((S_80172158_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172158_3 *)arg1)->unk_14 = 0;
        ((S_80172158_3 *)arg1)->unk_10 = 0;
        ((S_80172158_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80172158_1 *)arg2)->unk_24, ((S_80172158_1 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174EE0;
        func_80047784(
            arg2,
            D_80174EE0[((D_80083228 + ((S_80172158_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172158_0 *)arg0)->unk_9B++;
    }

block_18:
    temp_v0 = ((S_80172158_0 *)arg0)->unk_96 - 1;
    ((S_80172158_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 16) <= 0) {
        ((S_80172158_3 *)arg1)->unk_14 = 0;
        ((S_80172158_3 *)arg1)->unk_10 = 0;
        ((S_80172158_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80172158_1 *)arg2)->unk_24, ((S_80172158_1 *)arg2)->unk_25);
        func_800AD594(arg3, 3);
        func_800A4ACC(arg3);

        counter_base = (u8 *)&D_80083460;
        if (((S_80172158_4 *)counter_base)->unk_08.s != 0) {
            ((S_80172158_4 *)counter_base)->unk_08.u--;
        }

        temp_v1_3 = ((S_80172158_2 *)arg3)->unk_1C.u;
        if (temp_v1_3 & 0x2000) {
            if (((S_80172158_2 *)arg3)->unk_46 & 0x8000) {
                ((S_80172158_2 *)arg3)->unk_46 &= 0x7FFF;
            }
            goto block_28;
        }
        if (temp_v1_3 & 0x410) {
            goto block_28;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_28;
        }
        ((S_80172158_2 *)arg3)->unk_2A = func_800A0818(
            ((S_80172158_1 *)arg2)->unk_24, ((S_80172158_1 *)arg2)->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);

block_28:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_80172158_0 *)arg0)->unk_8C = D_80170E9C;
            func_800A9A04(arg3);
        }
    }
}

/* MECHANISM: The s32 address-taken sp18 local holds the 0x38 frame while args naturally occupy s0-s3.
   Separate axis/Delta compound chains expose the retail lbu/lh/shift order.
   Direct position += velocity followed by signed pre-decrement closes the final load/store rotation. */
