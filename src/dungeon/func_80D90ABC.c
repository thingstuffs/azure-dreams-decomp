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
    u8 pad_9C[0x4];
    s32 unk_A0;
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_801722BC_0;   /* arg0 in func_801722BC */

typedef struct S_801722BC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801722BC_1;   /* arg2 in func_801722BC */

typedef struct S_801722BC_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801722BC_2;   /* arg3 in func_801722BC */

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
} S_801722BC_4;   /* counter_base in func_801722BC */



extern void func_80047784(void *, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E68[];
extern u8 D_80173884[];
extern u8 D_8017388C[];

void func_801722BC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 temp_a0;
    s32 temp_acceleration;
    s32 temp_delta;
    s32 temp_delta_y;
    s32 temp_offset;
    s32 temp_position;
    s32 temp_velocity;
    s32 temp_timer;
    s32 temp_x;
    s16 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v0;
    s32 temp_v1;
    u8 *counter_base;

    temp_v1 = ((S_801722BC_0 *)arg0)->unk_9B;
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
    if (!(((S_801722BC_1 *)arg2)->unk_14 & 0x6000)) {
        goto block_18;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80173884;
    func_80047784(
        arg2,
        D_80173884[((D_80083228 + ((S_801722BC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801722BC_0 *)arg0)->unk_98 |= 8;
    ((S_801722BC_2 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
    ((S_801722BC_3 *)arg1)->unk_14 = 0xFFF00000;
    ((S_801722BC_0 *)arg0)->unk_A0 = 0;
    ((S_801722BC_0 *)arg0)->unk_9B++;

block_12:
    temp_a0 = ((S_801722BC_0 *)arg0)->unk_A4.s;
    ((S_801722BC_0 *)arg0)->unk_90 =
        ((S_801722BC_0 *)arg0)->unk_90 - ((S_801722BC_0 *)arg0)->unk_A0;
    if (temp_a0 != 0) {
        temp_x = ((S_801722BC_1 *)arg2)->unk_24 << 6;
        temp_delta = ((S_801722BC_3 *)arg1)->unk_02 - 0x20;
        temp_delta_y = ((S_801722BC_3 *)arg1)->unk_06 - 0x20;
        ((S_801722BC_3 *)arg1)->unk_0C =
            ((temp_x - temp_delta) << 16) /
            temp_a0;
        ((S_801722BC_3 *)arg1)->unk_10 =
            (((((S_801722BC_1 *)arg2)->unk_25 << 6) - temp_delta_y) << 16) /
            (s16)((S_801722BC_0 *)arg0)->unk_A4.s;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_timer = ((S_801722BC_0 *)arg0)->unk_A4.s;
        temp_velocity = ((S_801722BC_3 *)arg1)->unk_14;
        ASM_KEEP(temp_timer);   /* MATCH pin: retail register colouring depends on it */
        temp_acceleration =
            (temp_timer << 15) + (temp_timer << 13);
        temp_velocity += temp_acceleration;
        ((S_801722BC_3 *)arg1)->unk_14 = temp_velocity;
        ((S_801722BC_0 *)arg0)->unk_A0 += temp_velocity;
    }
    temp_position = ((S_801722BC_0 *)arg0)->unk_90;
    temp_offset = ((S_801722BC_0 *)arg0)->unk_A0;
    temp_v1_2 = ((S_801722BC_0 *)arg0)->unk_A4.u - 1;
    temp_position += temp_offset;
    ((S_801722BC_0 *)arg0)->unk_A4.s = temp_v1_2;
    ((S_801722BC_0 *)arg0)->unk_90 = temp_position;
    if (temp_v1_2 < 0) {
        ((S_801722BC_0 *)arg0)->unk_90 = 0;
        ((S_801722BC_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801722BC_2 *)arg3)->unk_1C.s |= 0x08000000;
        ((S_801722BC_0 *)arg0)->unk_9B++;
    }

block_16:
    if (((S_801722BC_2 *)arg3)->unk_1C.s & 0x08000000) {
        ((S_801722BC_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801722BC_3 *)arg1)->unk_14 = 0;
        ((S_801722BC_3 *)arg1)->unk_10 = 0;
        ((S_801722BC_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801722BC_1 *)arg2)->unk_24, ((S_801722BC_1 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017388C;
        func_80047784(
            arg2,
            D_8017388C[((D_80083228 + ((S_801722BC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)arg0)->unk_9B++;
    }

block_18:
    temp_v0 = ((S_801722BC_0 *)arg0)->unk_96 - 1;
    ((S_801722BC_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 16) <= 0) {
        ((S_801722BC_3 *)arg1)->unk_14 = 0;
        ((S_801722BC_3 *)arg1)->unk_10 = 0;
        ((S_801722BC_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801722BC_1 *)arg2)->unk_24, ((S_801722BC_1 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        counter_base = (u8 *)&D_80083460;
        if (((S_801722BC_4 *)counter_base)->unk_08.s != 0) {
            ((S_801722BC_4 *)counter_base)->unk_08.u--;
        }

        temp_v1_3 = ((S_801722BC_2 *)arg3)->unk_1C.u;
        if (temp_v1_3 & 0x2000) {
            if (((S_801722BC_2 *)arg3)->unk_46 & 0x8000) {
                ((S_801722BC_2 *)arg3)->unk_46 &= 0x7FFF;
            }
            goto block_28;
        }
        if (temp_v1_3 & 0x410) {
            goto block_28;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_28;
        }
        ((S_801722BC_2 *)arg3)->unk_2A = func_800A0818(
            ((S_801722BC_1 *)arg2)->unk_24, ((S_801722BC_1 *)arg2)->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);

block_28:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_801722BC_0 *)arg0)->unk_8C = D_80170E68;
            func_800A9A04(arg3);
        }
    }
}

/* MECHANISM: Four held arguments naturally give the 0x38 frame and s0/s1/s3/s2 save order.
   Named coordinate/delta and position/offset locals close both load-order residues.
   A guarded v0 timer pin plus a pre-load scheduling fence preserves the mflo nop and shift roles. */
