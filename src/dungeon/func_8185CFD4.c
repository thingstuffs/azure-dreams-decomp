#include "common.h"

typedef struct S_800247D4_0 {
    u8 pad_00[0x18];
    u32 * unk_18;
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x42];
    s32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u8 pad_E0[0x14];
    s32 unk_F4;
    s32 unk_F8;
} S_800247D4_0;   /* scratch in func_800247D4 */

typedef struct S_800247D4_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800247D4_1;   /* ctx in func_800247D4 */

typedef struct S_800247D4_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
} S_800247D4_2;   /* packet in func_800247D4 */

typedef struct S_800247D4_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x28];
    u16 unk_3A;
    u8 pad_3C[0x2];
    u16 unk_3E;
    u8 pad_40[0x2];
    u16 unk_42;
    u8 pad_44[0xE];
    u16 unk_52;
    u8 pad_54[0x2];
    u16 unk_56;
    u8 pad_58[0x2];
    u16 unk_5A;
} S_800247D4_3;   /* arg in func_800247D4 */

typedef struct S_800247D4_4 {
    u32 unk_00;
} S_800247D4_4;   /* (void *)scaled_index in func_800247D4 */



extern u8 D_80083160[];
extern void *D_80024008[];

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);

s32 func_800247D4(void *arg0)
{
    u8 *arg = arg0;
    u8 *initial_ctx = *(u8 **)D_80083160;
    u8 *ctx;
    register u32 t0_value ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 color_base;
    s32 high_mask;
    s32 phase;
    u8 *scratch;
    s32 count;
    u8 *packet;
    void *work84;
    void *work88;
    s32 delta;
    s32 angle;
    s32 index;
    register s32 v1_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 target_value;
    s32 a1_value;
    s32 y;
    s32 first_z;
    s32 second_z;
    s32 average;

    static void *const jt_keep[] = {
        &&case_early,
        &&case_middle,
        &&case_late,
        &&shared,
    };

    (void)jt_keep;
    ASM_USE_NV(initial_ctx);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    t0_value = 7;
    high_mask = 0xFFFF0000;
    color_base = 0x40;
    ASM_USE2_NV(high_mask, color_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    phase = 0x15;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(t0_value);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    count = (s32)t0_value;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_800247D4_0 *)scratch)->unk_18 = initial_ctx + 0xB0;

    do {
        t0_value = (u32)D_80083160;
        ASM_KEEP(t0_value);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ctx = *(u8 **)t0_value;
        packet = ((S_800247D4_1 *)ctx)->unk_8D0;
        ((S_800247D4_1 *)ctx)->unk_8D0 = packet + 0x14;

        ((S_800247D4_2 *)packet)->unk_00.at03.v = 4;
        ((S_800247D4_2 *)packet)->unk_07 = 0x50;

        ((S_800247D4_0 *)scratch)->unk_64 = ((S_800247D4_3 *)arg)->unk_3A;
        ((S_800247D4_0 *)scratch)->unk_66 = ((S_800247D4_3 *)arg)->unk_3E;
        ((S_800247D4_0 *)scratch)->unk_68 = ((S_800247D4_3 *)arg)->unk_42;

        angle = (phase % 8) << 9;
        ((S_800247D4_0 *)scratch)->unk_6C =
            ((S_800247D4_3 *)arg)->unk_52 + ((func_800644B8(angle) * 2) >> 8);
        ((S_800247D4_0 *)scratch)->unk_6E =
            ((S_800247D4_3 *)arg)->unk_56 + ((func_80064584(angle) * 2) >> 8);
        ((S_800247D4_0 *)scratch)->unk_70 = ((S_800247D4_3 *)arg)->unk_5A;

        index = ((S_800247D4_3 *)arg)->unk_10 - 1;
        if ((u32)index >= 15U) {
            goto shared;
        }
        goto *D_80024008[index];

case_early:
    {
        target_value = ((S_800247D4_0 *)scratch)->unk_6C;
        ASM_KEEP(target_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        v1_value = ((S_800247D4_0 *)scratch)->unk_64;
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        delta >>= 3;
        delta *= ((S_800247D4_3 *)arg)->unk_10 + 1;

        a1_value = delta >> 16;
        target_value = ((S_800247D4_0 *)scratch)->unk_6E;
        y = ((S_800247D4_0 *)scratch)->unk_66;
        delta &= 0xFFFF;
        delta |= (target_value - y) << 16;
        delta &= high_mask;
        ((S_800247D4_0 *)scratch)->unk_6C = v1_value + a1_value;
        delta >>= 3;
        delta *= ((S_800247D4_3 *)arg)->unk_10 + 1;

        a1_value = delta >> 16;
        target_value = ((S_800247D4_0 *)scratch)->unk_70;
        v1_value = ((S_800247D4_0 *)scratch)->unk_68;
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        y += a1_value;
        ((S_800247D4_0 *)scratch)->unk_6E = y;
        delta >>= 3;
        delta *= ((S_800247D4_3 *)arg)->unk_10 + 1;
        ((S_800247D4_0 *)scratch)->unk_70 = v1_value + (delta >> 16);

        v1_value = ((S_800247D4_3 *)arg)->unk_10;
        t0_value = 15;
        {
            register s32 color0 ASM_REG("$9") =
                (v1_value + 1) * (s32)t0_value;

            t0_value = 23;
            y = (v1_value + 1) * (s32)t0_value;
            ((S_800247D4_2 *)packet)->unk_04 = color_base;
            ((S_800247D4_2 *)packet)->unk_05 = color_base;
            ((S_800247D4_2 *)packet)->unk_06 = color_base;
            ((S_800247D4_2 *)packet)->unk_0D = color_base - ((7 - v1_value) * 8);
            {
                register s32 color0_out ASM_REG("$2") = 0x40 + color0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                ((S_800247D4_2 *)packet)->unk_0C = color0_out;
            }
            ((S_800247D4_2 *)packet)->unk_0E = 0x40 + y;
            goto shared;
        }
    }

case_middle:
        t0_value = 0x7F;
        target_value = 0xFF;
        ((S_800247D4_2 *)packet)->unk_04 = color_base;
        ((S_800247D4_2 *)packet)->unk_05 = color_base;
        ((S_800247D4_2 *)packet)->unk_06 = color_base;
        ((S_800247D4_2 *)packet)->unk_0C = (u8)t0_value;
        ((S_800247D4_2 *)packet)->unk_0D = 0;
        ((S_800247D4_2 *)packet)->unk_0E = (u8)target_value;
        goto shared;

case_late:
    {
        s32 color_step;

        target_value = ((S_800247D4_0 *)scratch)->unk_6C;
        ASM_KEEP(target_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        v1_value = ((S_800247D4_0 *)scratch)->unk_64;
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        delta >>= 3;
        delta *= ((S_800247D4_3 *)arg)->unk_10 - 7;

        a1_value = delta >> 16;
        target_value = ((S_800247D4_0 *)scratch)->unk_6E;
        y = ((S_800247D4_0 *)scratch)->unk_66;
        delta &= 0xFFFF;
        delta |= (target_value - y) << 16;
        delta &= high_mask;
        ((S_800247D4_0 *)scratch)->unk_64 = v1_value + a1_value;
        delta >>= 3;
        delta *= ((S_800247D4_3 *)arg)->unk_10 - 7;

        a1_value = delta >> 16;
        target_value = ((S_800247D4_0 *)scratch)->unk_70;
        v1_value = ((S_800247D4_0 *)scratch)->unk_68;
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        y += a1_value;
        ((S_800247D4_0 *)scratch)->unk_66 = y;
        delta >>= 3;
        delta *= ((S_800247D4_3 *)arg)->unk_10 - 7;
        ((S_800247D4_0 *)scratch)->unk_68 = v1_value + (delta >> 16);

        v1_value = ((S_800247D4_3 *)arg)->unk_10;
        color_step = v1_value - 7;
        t0_value = 15;
        {
            register s32 color0 ASM_REG("$9") =
                color_step * (s32)t0_value;

            t0_value = 23;
            y = color_step * (s32)t0_value;
            ((S_800247D4_2 *)packet)->unk_0D = 0;
            t0_value = 0x7F;
            color_step = 0xFF;
            ((S_800247D4_2 *)packet)->unk_0C = (u8)t0_value;
            t0_value = 15;
            v1_value = (t0_value - v1_value) * 8;
            ((S_800247D4_2 *)packet)->unk_0E = (u8)color_step;
            {
                register s32 color0_out ASM_REG("$2") = 0x40 + color0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                ((S_800247D4_2 *)packet)->unk_04 = color0_out;
            }
            ((S_800247D4_2 *)packet)->unk_05 = (u8)v1_value;
            ((S_800247D4_2 *)packet)->unk_06 = 0x40 + y;
        }
    }

shared:
        work84 = scratch + 0x84;
        work88 = scratch + 0x88;
        {
            u8 *src0 = scratch + 0x64;
            u8 *dst0 = scratch + 0xD8;
            ASM_USE2_NV(src0, dst0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            first_z = func_80065420(src0, dst0, work84, work88);
        }
        ((S_800247D4_0 *)scratch)->unk_F4 = first_z;
        {
            u8 *src1 = scratch + 0x6C;
            u8 *dst1 = scratch + 0xDC;
            ASM_USE2_NV(src1, dst1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            second_z = func_80065420(src1, dst1, work84, work88);
        }
        ((S_800247D4_0 *)scratch)->unk_F8 = second_z;

        ((S_800247D4_2 *)packet)->unk_08 = ((S_800247D4_0 *)scratch)->unk_D8;
        ((S_800247D4_2 *)packet)->unk_0A = ((S_800247D4_0 *)scratch)->unk_DA;
        ((S_800247D4_2 *)packet)->unk_10 = ((S_800247D4_0 *)scratch)->unk_DC;
        ((S_800247D4_2 *)packet)->unk_12 = ((S_800247D4_0 *)scratch)->unk_DE;

        {
            s32 sum = ((S_800247D4_0 *)scratch)->unk_F4;
            s32 sign = ((S_800247D4_0 *)scratch)->unk_F8;

            sum += sign;
            sign = (u32)sum >> 31;
            sum += sign;
            a1_value = sum >> 1;
        }
        ((S_800247D4_0 *)scratch)->unk_B4 = a1_value;
        if ((u32)a1_value < 0x1E0U) {
            u32 table_low = 0x00FFFFFF;
            u32 *ordering_table;

            {
                u32 scaled_index =
                    (u32)a1_value << 2;
                u32 *first_table =
                    ((S_800247D4_0 *)scratch)->unk_18;

                {
                    u32 table_high = 0xFF000000;

                    scaled_index += (u32)first_table;
                    ((S_800247D4_2 *)packet)->unk_00.at00.v =
                        (((S_800247D4_2 *)packet)->unk_00.at00.v & table_high) |
                        (((S_800247D4_4 *)((void *)scaled_index))->unk_00 & table_low);
                    ordering_table = ((S_800247D4_0 *)scratch)->unk_18;
                    ordering_table[((S_800247D4_0 *)scratch)->unk_B4] =
                        (ordering_table[((S_800247D4_0 *)scratch)->unk_B4] & table_high) |
                        ((u32)packet & table_low);
                }
            }
        }

        t0_value = (u32)count;
        ASM_KEEP(t0_value);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        phase -= 3;
        t0_value -= 1;
        count = (s32)t0_value;
    } while ((s32)t0_value >= 0);

    return 0;
}
