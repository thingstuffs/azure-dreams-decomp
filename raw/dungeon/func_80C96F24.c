#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 bytes[12];
} Copy12;

extern u8 D_80174320[12];
extern u8 D_80174374[12];
extern u8 D_80175330[12];

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern void *memcpy(void *, const void *, u32);

void func_80C96F24(void *arg0, void *arg1) {
    volatile u16 outer;
    register s32 row_offset;

    FIELD(arg0, u16, 0xA4) = 0;
    outer = 0;

    do {
        register s32 outer_index ASM_REG("$22");
        register s32 inner ASM_REG("$21");

        {
            register s32 outer_raw ASM_REG("$6");
            register s32 outer_extended ASM_REG("$2");

            ASM_SET(outer_raw);
            outer_raw = outer;
            ASM_KEEP_NV(outer_raw);
            inner = 0;
            outer_extended = outer_raw << 16;
            outer_index = outer_extended >> 16;
        }
        ASM_KEEP_NV(outer_index);
        row_offset = outer_index * 0x10;

        do {
            register s32 var_s7 ASM_REG("$23") = 0;
            register s32 var_s3 ASM_REG("$19") = 0;
            register s32 outer_one ASM_REG("$6");
            register s32 outer_two ASM_REG("$2");
            void *obj;

            if (outer_index == 0) {
                var_s3 = 0x18;
            }
            outer_one = 1;
            ASM_KEEP_NV(outer_one);
            outer_two = 2;
            if (outer_index == outer_one) {
                var_s3 = 0x18;
                var_s7 = 0x18;
            }
            if (outer_index == outer_two) {
                var_s3 = 0;
                var_s7 = 0x18;
            }

            obj = func_8003FC64(0x12);
            if (obj != 0) {
                register void *obj_call_arg ASM_REG("$4");
                register void *state ASM_REG("$18");
                register void *work ASM_REG("$20");
                register void *arg0_reload ASM_REG("$6");
                void *position;
                register s32 work_value ASM_REG("$2");
                s16 value;
                register s32 angle0 ASM_REG("$16");
                register s32 angle1 ASM_REG("$17");

                obj_call_arg = obj;
                ASM_KEEP_NV(obj_call_arg);
                work = (u8 *)obj + 0x20;
                ASM_KEEP_NV(work);

                work_value = 0x42;
                ASM_KEEP_NV(work_value);
                FIELD(work, s16, 0x24) = work_value;
                ASM_SET(work_value);
                work_value = 0x17;
                ASM_KEEP_NV(work_value);
                FIELD(work, s16, 0x26) = 0;
                FIELD(work, s16, 0x2A) = inner;
                ASM_SET(arg0_reload);
                arg0_reload = arg0;
                ASM_KEEP_NV(arg0_reload);
                FIELD(work, s16, 0x2C) =
                    work_value - FIELD(arg0_reload, u16, 0xA4);
                FIELD(obj, void *, 0x10) = D_80174374;
                func_8004491C(obj_call_arg, D_80174320, arg0_reload);

                state = FIELD(obj, u8 *, 0x0C);
                FIELD(state, s16, 0x10) = 0x20;
                FIELD(state, u16, 0x14) |= 0x0C;

                {
                    register void *arg1_reload ASM_REG("$6");

                    ASM_SET(arg1_reload);
                    arg1_reload = arg1;
                    ASM_KEEP_NV(arg1_reload);
                    position = FIELD(obj, u8 *, 0x08);
                    FIELD(position, s32, 0x00) =
                        FIELD(arg1_reload, s32, 0x00);
                    FIELD(position, s32, 0x04) =
                        FIELD(arg1_reload, s32, 0x04);
                    FIELD(position, s32, 0x08) =
                        FIELD(arg1_reload, s32, 0x08) + 0x200000;
                }

                state = FIELD(obj, u8 *, 0x0C);
                FIELD(state, s16, 0x1E) = 0x1000;
                FIELD(state, s16, 0x1C) = 0x1000;
                FIELD(state, u8, 0x0E) = 0x80;
                FIELD(state, u8, 0x0D) = 0x80;
                FIELD(state, u8, 0x0C) = 0x80;

                FIELD(obj, u8, 0x20) =
                    (func_80069EF8() & 0x1F) + 0x10 + row_offset;
                FIELD(work, u8, 0x01) =
                    (func_80069EF8() & 0x1F) + 0x10 + row_offset;
                FIELD(work, u8, 0x02) =
                    (func_80069EF8() & 0x1F) + 0x10 + row_offset;

                {
                    register s32 inner_one ASM_REG("$6");
                    s32 inner_value = (s16)inner;

                    ASM_SET(inner_one);
                    inner_one = 1;
                    ASM_KEEP_DEP_NV(inner_one, inner_value);
                    if ((inner_value == inner_one) || (inner_value == 6)) {
                        FIELD(obj, u8, 0x20) += 0x0A;
                        FIELD(work, u8, 0x01) += 0x0A;
                        FIELD(work, u8, 0x02) += 0x0A;
                    }
                }
                if (((s16)inner == 2) || ((s16)inner == 5)) {
                    FIELD(work, u8, 0x00) += 0x14;
                    FIELD(work, u8, 0x01) += 0x14;
                    FIELD(work, u8, 0x02) += 0x14;
                }
                if ((u16)(inner - 3) < 2U) {
                    FIELD(work, u8, 0x00) += 0x1E;
                    FIELD(work, u8, 0x01) += 0x1E;
                    FIELD(work, u8, 0x02) += 0x1E;
                }

                {
                    register u8 *copy_source ASM_REG("$6");
                    copy_source = D_80175330;
                    *(Copy12 *)((u8 *)work + 0x7A) = *(Copy12 *)copy_source;
                }
                ASM_SCHED_BARRIER();

                {
                    register s32 product ASM_REG("$6");
                    register s32 factor_s2 ASM_REG("$18");
                    register void *copy_dest ASM_REG("$2");
                    register s32 call_angle ASM_REG("$4");
                    s32 shifted;
                    s32 trig;

                    ASM_SET(product);
                    value = (s16)inner;
                    angle1 = (value + 1) << 9;
                    ASM_KEEP_NV(angle1);
                    call_angle = angle1;
                    ASM_KEEP_NV(call_angle);
                    ASM_KEEP_DEP_NV(work, call_angle);
                    copy_dest = work + 0x7A;
                    ASM_KEEP_DEP_NV(copy_dest, angle1);
                    FIELD(state, void *, 0x08) = copy_dest;

                    product = var_s3 * func_80064584(call_angle);
                    angle0 = value << 9;
                    ASM_KEEP_NV(angle0);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x44) = shifted;
                    product = var_s3 * func_80064584(angle0);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x4A) = shifted;
                    trig = func_80064584(angle1);
                    ASM_SET(factor_s2);
                    factor_s2 = var_s7;
                    ASM_KEEP_NV(factor_s2);
                    product = factor_s2 * trig;
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x50) = shifted;
                    product = factor_s2 * func_80064584(angle0);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x56) = shifted;
                    product = var_s3 * func_800644B8(angle1);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x46) = shifted;
                    product = var_s3 * func_800644B8(angle0);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x4C) = shifted;
                    product = factor_s2 * func_800644B8(angle1);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x52) = shifted;
                    product = factor_s2 * func_800644B8(angle0);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);
                    FIELD(work, s16, 0x58) = shifted;
                }

                {
                    register s32 outer_one_end ASM_REG("$6");
                    register s32 outer_two_end ASM_REG("$2");
                    s16 right = 0;
                    s16 left = right;

                    if (outer_index == 0) {
                        left = -0x14;
                    }
                    outer_one_end = 1;
                    ASM_KEEP_NV(outer_one_end);
                    outer_two_end = 2;
                    if (outer_index == outer_one_end) {
                        left = -0x2E;
                        right = -0x14;
                    }
                    if (outer_index == outer_two_end) {
                        left = -0x42;
                        right = -0x2E;
                    }
                    FIELD(work, s16, 0x4E) = left;
                    FIELD(work, s16, 0x48) = left;
                    FIELD(work, s16, 0x5A) = right;
                    FIELD(work, s16, 0x54) = right;
                }
            }

            {
                register s32 loop_value ASM_REG("$2");
                register void *arg0_counter ASM_REG("$6");
                register u16 counter_value ASM_REG("$3");

                loop_value = inner + 1;
                ASM_KEEP_NV(loop_value);
                inner = loop_value;
                loop_value <<= 16;
                ASM_SET(arg0_counter);
                arg0_counter = arg0;
                loop_value >>= 16;
                counter_value = FIELD(arg0_counter, u16, 0xA4);
                loop_value = loop_value < 8;
                counter_value++;
                ASM_USE2_NV(arg0_counter, counter_value);
                FIELD(arg0_counter, u16, 0xA4) = counter_value;
                if (loop_value) {
                    continue;
                }
                break;
            }
        } while (1);

        {
            register s32 outer_next_raw ASM_REG("$6");
            s16 next_outer;

            ASM_SET(outer_next_raw);
            outer_next_raw = outer;
            ASM_KEEP_NV(outer_next_raw);
            next_outer = (s16)(outer_next_raw + 1);
            ASM_USE2_NV(outer_next_raw, next_outer);
            outer = (u16)next_outer;
            if (next_outer >= 3) {
                break;
            }
        }
    } while (1);
}
