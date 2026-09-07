#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register u32 t0_value ASM_REG("$8");
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
    register s32 v1_value ASM_REG("$3");
    s32 target_value;
    register s32 a1_value ASM_REG("$5");
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
    ASM_USE_NV(initial_ctx);
    t0_value = 7;
    ASM_USE_NV(t0_value);
    high_mask = 0xFFFF0000;
    ASM_USE_NV(high_mask);
    color_base = 0x40;
    ASM_USE2_NV(high_mask, color_base);
    phase = 0x15;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(t0_value);
    count = (s32)t0_value;
    ASM_SCHED_BARRIER();
    FIELD(scratch, u32 *, 0x18) = initial_ctx + 0xB0;

    do {
        t0_value = (u32)D_80083160;
        ASM_KEEP(t0_value);
        ctx = *(u8 **)t0_value;
        packet = FIELD(ctx, u8 *, 0x8D0);
        FIELD(ctx, u8 *, 0x8D0) = packet + 0x14;

        FIELD(packet, u8, 3) = 4;
        FIELD(packet, u8, 7) = 0x50;

        FIELD(scratch, u16, 0x64) = FIELD(arg, u16, 0x3A);
        FIELD(scratch, u16, 0x66) = FIELD(arg, u16, 0x3E);
        FIELD(scratch, u16, 0x68) = FIELD(arg, u16, 0x42);

        angle = (phase % 8) << 9;
        FIELD(scratch, u16, 0x6C) =
            FIELD(arg, u16, 0x52) + ((func_800644B8(angle) * 2) >> 8);
        FIELD(scratch, u16, 0x6E) =
            FIELD(arg, u16, 0x56) + ((func_80064584(angle) * 2) >> 8);
        FIELD(scratch, u16, 0x70) = FIELD(arg, u16, 0x5A);

        index = FIELD(arg, s16, 0x10) - 1;
        if ((u32)index >= 15U) {
            goto shared;
        }
        goto *D_80024008[index];

case_early:
    {
        target_value = FIELD(scratch, u16, 0x6C);
        ASM_KEEP(target_value);
        v1_value = FIELD(scratch, u16, 0x64);
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        delta >>= 3;
        delta *= FIELD(arg, s16, 0x10) + 1;

        a1_value = delta >> 16;
        target_value = FIELD(scratch, u16, 0x6E);
        y = FIELD(scratch, u16, 0x66);
        delta &= 0xFFFF;
        delta |= (target_value - y) << 16;
        delta &= high_mask;
        FIELD(scratch, u16, 0x6C) = v1_value + a1_value;
        delta >>= 3;
        delta *= FIELD(arg, s16, 0x10) + 1;

        a1_value = delta >> 16;
        target_value = FIELD(scratch, u16, 0x70);
        v1_value = FIELD(scratch, u16, 0x68);
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        y += a1_value;
        FIELD(scratch, u16, 0x6E) = y;
        delta >>= 3;
        delta *= FIELD(arg, s16, 0x10) + 1;
        FIELD(scratch, u16, 0x70) = v1_value + (delta >> 16);

        v1_value = FIELD(arg, s16, 0x10);
        t0_value = 15;
        {
            register s32 color0 ASM_REG("$9") =
                (v1_value + 1) * (s32)t0_value;

            t0_value = 23;
            y = (v1_value + 1) * (s32)t0_value;
            FIELD(packet, u8, 4) = color_base;
            FIELD(packet, u8, 5) = color_base;
            FIELD(packet, u8, 6) = color_base;
            FIELD(packet, u8, 0xD) = color_base - ((7 - v1_value) * 8);
            {
                register s32 color0_out ASM_REG("$2") = 0x40 + color0;

                FIELD(packet, u8, 0xC) = color0_out;
            }
            FIELD(packet, u8, 0xE) = 0x40 + y;
            goto shared;
        }
    }

case_middle:
        t0_value = 0x7F;
        ASM_KEEP(t0_value);
        target_value = 0xFF;
        ASM_KEEP(target_value);
        FIELD(packet, u8, 4) = color_base;
        FIELD(packet, u8, 5) = color_base;
        FIELD(packet, u8, 6) = color_base;
        FIELD(packet, u8, 0xC) = (u8)t0_value;
        FIELD(packet, u8, 0xD) = 0;
        FIELD(packet, u8, 0xE) = (u8)target_value;
        goto shared;

case_late:
    {
        s32 color_step;

        target_value = FIELD(scratch, u16, 0x6C);
        ASM_KEEP(target_value);
        v1_value = FIELD(scratch, u16, 0x64);
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        delta >>= 3;
        delta *= FIELD(arg, s16, 0x10) - 7;

        a1_value = delta >> 16;
        target_value = FIELD(scratch, u16, 0x6E);
        y = FIELD(scratch, u16, 0x66);
        delta &= 0xFFFF;
        delta |= (target_value - y) << 16;
        delta &= high_mask;
        FIELD(scratch, u16, 0x64) = v1_value + a1_value;
        delta >>= 3;
        delta *= FIELD(arg, s16, 0x10) - 7;

        a1_value = delta >> 16;
        target_value = FIELD(scratch, u16, 0x70);
        v1_value = FIELD(scratch, u16, 0x68);
        delta &= 0xFFFF;
        delta |= (target_value - v1_value) << 16;
        delta &= high_mask;
        y += a1_value;
        FIELD(scratch, u16, 0x66) = y;
        delta >>= 3;
        delta *= FIELD(arg, s16, 0x10) - 7;
        FIELD(scratch, u16, 0x68) = v1_value + (delta >> 16);

        v1_value = FIELD(arg, s16, 0x10);
        color_step = v1_value - 7;
        t0_value = 15;
        {
            register s32 color0 ASM_REG("$9") =
                color_step * (s32)t0_value;

            t0_value = 23;
            y = color_step * (s32)t0_value;
            FIELD(packet, u8, 0xD) = 0;
            t0_value = 0x7F;
            color_step = 0xFF;
            FIELD(packet, u8, 0xC) = (u8)t0_value;
            t0_value = 15;
            v1_value = (t0_value - v1_value) * 8;
            FIELD(packet, u8, 0xE) = (u8)color_step;
            {
                register s32 color0_out ASM_REG("$2") = 0x40 + color0;

                FIELD(packet, u8, 4) = color0_out;
            }
            FIELD(packet, u8, 5) = (u8)v1_value;
            FIELD(packet, u8, 6) = 0x40 + y;
        }
    }

shared:
        work84 = scratch + 0x84;
        work88 = scratch + 0x88;
        {
            u8 *src0 = scratch + 0x64;
            u8 *dst0 = scratch + 0xD8;
            ASM_USE2_NV(src0, dst0);
            first_z = func_80065420(src0, dst0, work84, work88);
        }
        FIELD(scratch, s32, 0xF4) = first_z;
        {
            u8 *src1 = scratch + 0x6C;
            u8 *dst1 = scratch + 0xDC;
            ASM_USE2_NV(src1, dst1);
            second_z = func_80065420(src1, dst1, work84, work88);
        }
        FIELD(scratch, s32, 0xF8) = second_z;

        FIELD(packet, u16, 8) = FIELD(scratch, u16, 0xD8);
        FIELD(packet, u16, 0xA) = FIELD(scratch, u16, 0xDA);
        FIELD(packet, u16, 0x10) = FIELD(scratch, u16, 0xDC);
        FIELD(packet, u16, 0x12) = FIELD(scratch, u16, 0xDE);

        {
            register s32 sum ASM_REG("$2") = FIELD(scratch, s32, 0xF4);
            register s32 sign ASM_REG("$3") = FIELD(scratch, s32, 0xF8);

            ASM_KEEP(sum);
            ASM_KEEP(sign);
            sum += sign;
            sign = (u32)sum >> 31;
            sum += sign;
            ASM_KEEP(sum);
            ASM_KEEP(sign);
            a1_value = sum >> 1;
        }
        ASM_KEEP(a1_value);
        FIELD(scratch, s32, 0xB4) = a1_value;
        if ((u32)a1_value < 0x1E0U) {
            register u32 table_low ASM_REG("$4") = 0x00FFFFFF;
            u32 *ordering_table;

            ASM_KEEP(table_low);
            {
                register u32 scaled_index ASM_REG("$2") =
                    (u32)a1_value << 2;
                register u32 *first_table ASM_REG("$3") =
                    FIELD(scratch, u32 *, 0x18);

                ASM_KEEP(scaled_index);
                ASM_KEEP(first_table);
                {
                    register u32 table_high ASM_REG("$5") = 0xFF000000;

                    ASM_KEEP(table_high);
                    scaled_index += (u32)first_table;
                    ASM_KEEP(scaled_index);
                    FIELD(packet, u32, 0) =
                        (FIELD(packet, u32, 0) & table_high) |
                        (FIELD((void *)scaled_index, u32, 0) & table_low);
                    ordering_table = FIELD(scratch, u32 *, 0x18);
                    ordering_table[FIELD(scratch, s32, 0xB4)] =
                        (ordering_table[FIELD(scratch, s32, 0xB4)] & table_high) |
                        ((u32)packet & table_low);
                }
            }
        }

        t0_value = (u32)count;
        ASM_KEEP(t0_value);
        phase -= 3;
        t0_value -= 1;
        count = (s32)t0_value;
    } while ((s32)t0_value >= 0);

    return 0;
}
