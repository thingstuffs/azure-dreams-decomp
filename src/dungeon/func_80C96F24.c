#include "common.h"

typedef struct S_80C96F24_0 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} S_80C96F24_0;   /* arg0 in func_80C96F24 */

typedef struct S_80C96F24_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x21];
    s16 unk_24;
    s16 unk_26;
    u8 pad_28[0x2];
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x16];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} S_80C96F24_1;   /* work in func_80C96F24 */

typedef struct S_80C96F24_2 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} S_80C96F24_2;   /* arg0_reload in func_80C96F24 */

typedef struct S_80C96F24_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} S_80C96F24_3;   /* obj in func_80C96F24 */

typedef struct S_80C96F24_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80C96F24_4;   /* state in func_80C96F24 */

typedef struct S_80C96F24_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C96F24_5;   /* position in func_80C96F24 */

typedef struct S_80C96F24_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C96F24_6;   /* arg1_reload in func_80C96F24 */

typedef struct S_80C96F24_7 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} S_80C96F24_7;   /* arg0_counter in func_80C96F24 */



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

void func_80C96F24(S_80C96F24_0 *arg0, void *arg1) {
    volatile u16 outer;
    register s32 row_offset;

    arg0->unk_A4 = 0;
    outer = 0;

    do {
        s32 outer_index;
        register s32 inner ASM_REG("$21");   /* MATCH pin: keeps a constant in a register as retail does */

        {
            register s32 outer_raw ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 outer_extended ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            outer_raw = outer;
            ASM_KEEP_NV(outer_raw);   /* MATCH pin: load-bearing for the whole function shape */
            inner = 0;
            outer_extended = outer_raw << 16;
            outer_index = outer_extended >> 16;
        }
        row_offset = outer_index * 0x10;

        do {
            s32 var_s7 = 0;
            s32 var_s3 = 0;
            register s32 outer_one ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
            s32 outer_two;
            void *obj;

            if (outer_index == 0) {
                var_s3 = 0x18;
            }
            outer_one = 1;
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
                register void *obj_call_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
                void *state;
                register void *work ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
                void *arg0_reload;
                S_80C96F24_5 *position;
                register s32 work_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                s16 value;
                s32 angle0;
                s32 angle1;

                obj_call_arg = obj;
                work = (u8 *)obj + 0x20;

                work_value = 0x42;
                ((S_80C96F24_1 *)work)->unk_24 = work_value;
                work_value = 0x17;
                ((S_80C96F24_1 *)work)->unk_26 = 0;
                ((S_80C96F24_1 *)work)->unk_2A = inner;
                ASM_SET(arg0_reload);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                arg0_reload = arg0;
                ASM_KEEP_NV(arg0_reload);   /* MATCH pin: keeps a statement from moving across a call/branch */
                ((S_80C96F24_1 *)work)->unk_2C =
                    work_value - ((S_80C96F24_2 *)arg0_reload)->unk_A4;
                ((S_80C96F24_3 *)obj)->unk_10 = D_80174374;
                func_8004491C(obj_call_arg, D_80174320, arg0_reload);

                state = ((S_80C96F24_3 *)obj)->unk_0C;
                ((S_80C96F24_4 *)state)->unk_10 = 0x20;
                ((S_80C96F24_4 *)state)->unk_14 |= 0x0C;

                {
                    register void *arg1_reload ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */

                    ASM_SET(arg1_reload);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    arg1_reload = arg1;
                    ASM_KEEP_NV(arg1_reload);   /* MATCH pin: load-bearing for the whole function shape */
                    position = ((S_80C96F24_3 *)obj)->unk_08;
                    position->unk_00 =
                        ((S_80C96F24_6 *)arg1_reload)->unk_00;
                    position->unk_04 =
                        ((S_80C96F24_6 *)arg1_reload)->unk_04;
                    position->unk_08 =
                        ((S_80C96F24_6 *)arg1_reload)->unk_08 + 0x200000;
                }

                state = ((S_80C96F24_3 *)obj)->unk_0C;
                ((S_80C96F24_4 *)state)->unk_1E = 0x1000;
                ((S_80C96F24_4 *)state)->unk_1C = 0x1000;
                ((S_80C96F24_4 *)state)->unk_0E = 0x80;
                ((S_80C96F24_4 *)state)->unk_0D = 0x80;
                ((S_80C96F24_4 *)state)->unk_0C = 0x80;

                ((S_80C96F24_3 *)obj)->unk_20 =
                    (func_80069EF8() & 0x1F) + 0x10 + row_offset;
                ((S_80C96F24_1 *)work)->unk_01 =
                    (func_80069EF8() & 0x1F) + 0x10 + row_offset;
                ((S_80C96F24_1 *)work)->unk_02 =
                    (func_80069EF8() & 0x1F) + 0x10 + row_offset;

                {
                    register s32 inner_one ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
                    s32 inner_value = (s16)inner;

                    ASM_SET(inner_one);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    inner_one = 1;
                    if ((inner_value == inner_one) || (inner_value == 6)) {
                        ((S_80C96F24_3 *)obj)->unk_20 += 0x0A;
                        ((S_80C96F24_1 *)work)->unk_01 += 0x0A;
                        ((S_80C96F24_1 *)work)->unk_02 += 0x0A;
                    }
                }
                if (((s16)inner == 2) || ((s16)inner == 5)) {
                    ((S_80C96F24_1 *)work)->unk_00 += 0x14;
                    ((S_80C96F24_1 *)work)->unk_01 += 0x14;
                    ((S_80C96F24_1 *)work)->unk_02 += 0x14;
                }
                if ((u16)(inner - 3) < 2U) {
                    ((S_80C96F24_1 *)work)->unk_00 += 0x1E;
                    ((S_80C96F24_1 *)work)->unk_01 += 0x1E;
                    ((S_80C96F24_1 *)work)->unk_02 += 0x1E;
                }

                {
                    u8 *copy_source;
                    copy_source = D_80175330;
                    *(Copy12 *)((u8 *)work + 0x7A) = *(Copy12 *)copy_source;
                }

                {
                    register s32 product ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
                    s32 factor_s2;
                    void *copy_dest;
                    s32 call_angle;
                    s32 shifted;
                    s32 trig;

                    value = (s16)inner;
                    angle1 = (value + 1) << 9;
                    call_angle = angle1;
                    ASM_KEEP_DEP_NV(work, call_angle);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    copy_dest = work + 0x7A;
                    ((S_80C96F24_4 *)state)->unk_08 = copy_dest;

                    product = var_s3 * func_80064584(call_angle);
                    angle0 = value << 9;
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_44 = shifted;
                    product = var_s3 * func_80064584(angle0);
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_4A = shifted;
                    trig = func_80064584(angle1);
                    factor_s2 = var_s7;
                    ASM_KEEP_NV(factor_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    product = factor_s2 * trig;
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_50 = shifted;
                    product = factor_s2 * func_80064584(angle0);
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_56 = shifted;
                    product = var_s3 * func_800644B8(angle1);
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_46 = shifted;
                    product = var_s3 * func_800644B8(angle0);
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_4C = shifted;
                    product = factor_s2 * func_800644B8(angle1);
                    shifted = product >> 12;
                    ((S_80C96F24_1 *)work)->unk_52 = shifted;
                    product = factor_s2 * func_800644B8(angle0);
                    shifted = product >> 12;
                    ASM_USE2_NV(product, shifted);   /* MATCH pin: load-bearing for the whole function shape */
                    ((S_80C96F24_1 *)work)->unk_58 = shifted;
                }

                {
                    register s32 outer_one_end ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
                    s32 outer_two_end;
                    s16 right = 0;
                    s16 left = right;

                    if (outer_index == 0) {
                        left = -0x14;
                    }
                    outer_one_end = 1;
                    outer_two_end = 2;
                    if (outer_index == outer_one_end) {
                        left = -0x2E;
                        right = -0x14;
                    }
                    if (outer_index == outer_two_end) {
                        left = -0x42;
                        right = -0x2E;
                    }
                    ((S_80C96F24_1 *)work)->unk_4E = left;
                    ((S_80C96F24_1 *)work)->unk_48 = left;
                    ((S_80C96F24_1 *)work)->unk_5A = right;
                    ((S_80C96F24_1 *)work)->unk_54 = right;
                }
            }

            {
                s32 loop_value;
                register void *arg0_counter ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
                u16 counter_value;

                loop_value = inner + 1;
                inner = loop_value;
                loop_value <<= 16;
                arg0_counter = arg0;
                loop_value >>= 16;
                counter_value = ((S_80C96F24_7 *)arg0_counter)->unk_A4;
                loop_value = loop_value < 8;
                counter_value++;
                ((S_80C96F24_7 *)arg0_counter)->unk_A4 = counter_value;
                if (loop_value) {
                    continue;
                }
                break;
            }
        } while (1);

        {
            register s32 outer_next_raw ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
            s16 next_outer;

            outer_next_raw = outer;
            next_outer = (s16)(outer_next_raw + 1);
            ASM_USE2_NV(outer_next_raw, next_outer);   /* MATCH pin: load-bearing for the whole function shape */
            outer = (u16)next_outer;
            if (next_outer >= 3) {
                break;
            }
        }
    } while (1);
}
