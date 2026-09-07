#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

    temp_v1 = FIELD(arg0, u8, 0x9B);
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
    if (((FIELD(arg2, s8, 4) == 1) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, s16, 0x9E) = 6;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B)++;
        goto block_12;
    }
    goto block_18;

block_12:
    temp_a0 = FIELD(arg0, s16, 0x9E);
    FIELD(arg0, s32, 0x90) =
        FIELD(arg0, s32, 0x90) - FIELD(arg0, s32, 0xA0);
    if (temp_a0 != 0) {
        temp_axis = FIELD(arg2, u8, 0x24);
        temp_delta = FIELD(arg1, s16, 2);
        temp_axis <<= 6;
        temp_delta -= 0x20;
        temp_axis -= temp_delta;
        temp_axis <<= 16;
        FIELD(arg1, s32, 0x0C) = temp_axis / temp_a0;
        temp_delta = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) - temp_delta) << 16) /
            (s16)FIELD(arg0, s16, 0x9E);
        FIELD(arg0, s32, 0xA0) =
            (-func_800644B8(FIELD(arg0, s16, 0x9E) * 0x155)) << 9;
    }
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    temp_v1_2 = --FIELD(arg0, s16, 0x9E);
    if (temp_v1_2 < 0) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

block_16:
    if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg2, u8 *, 0x2C) = D_80174EE0;
        func_80047784(
            arg2,
            D_80174EE0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B)++;
    }

block_18:
    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0;
    if ((temp_v0 << 16) <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 3);
        func_800A4ACC(arg3);

        counter_base = (u8 *)&D_80083460;
        if (FIELD(counter_base, s16, 8) != 0) {
            FIELD(counter_base, u16, 8)--;
        }

        temp_v1_3 = FIELD(arg3, s32, 0x1C);
        if (temp_v1_3 & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
            goto block_28;
        }
        if (temp_v1_3 & 0x410) {
            goto block_28;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_28;
        }
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);

block_28:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, u8 *, 0x8C) = D_80170E9C;
            func_800A9A04(arg3);
        }
    }
}

/* MECHANISM: The s32 address-taken sp18 local holds the 0x38 frame while args naturally occupy s0-s3.
   Separate axis/Delta compound chains expose the retail lbu/lh/shift order.
   Direct position += velocity followed by signed pre-decrement closes the final load/store rotation. */
