/* row func_8132E2FC, true base 0x801652FC -- exemplar-seeded from landed
 * func_80BC1528 (MATCH @2.7.2-cdk-G0, gate_verified). Opcode-sequence
 * similarity 0.9843. Ordinary code: no symbol alias, no .text section
 * attribute, no literal word arrays, first word is the prologue.
 *
 * Adaptation measured off the retail stream:
 *   - one fewer parameter (exemplar's arg2 is gone; the value stored at
 *     obj+0x20 / tail+8 is arg1 here), so every later arg shifts one slot
 *   - `FIELD(tail, s16, 0x14) = arg1` is absent
 *   - the six vector fields sit 0xC higher (0x36->0x42 ... 0x54->0x60)
 *   - the z bias is -40, not -100
 *   - the two overlay data symbols are this image's
 */
#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C();
extern u8 D_80164BC4[];
extern u8 D_80165164[];

void func_801652FC(
    void *arg0, s32 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5)
{
    register void *saved_arg0 ASM_REG("$17") = arg0;
    register s32 saved_arg1 ASM_REG("$23") = arg1;
    register s32 saved_arg3 ASM_REG("$22") = arg2;
    register s32 saved_arg4 ASM_REG("$19") = arg3;
    register s32 saved_arg5 ASM_REG("$20") = arg4;
    register s32 saved_arg6 ASM_REG("$21") = arg5;
    register void *obj ASM_REG("$18");
    register void *tail ASM_REG("$16");
    register s32 narrowed_arg3;
    register s32 divisor ASM_REG("$3");
    s32 numerator_x;
    register s32 numerator_y ASM_REG("$2");
    s32 quotient_x;
    register s32 quotient_y ASM_REG("$5");
    s32 quotient_z;
    s32 rounded_x;
    register s32 rounded_y ASM_REG("$2");
    s32 rounded_z;

    obj = func_8003FD64(0x211, saved_arg0);
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = D_80165164;

        FIELD(FIELD(obj, void *, 8), s16, 2) =
            FIELD(FIELD(saved_arg0, void *, 8), u16, 2) + saved_arg4;
        FIELD(FIELD(obj, void *, 8), s16, 6) =
            FIELD(FIELD(saved_arg0, void *, 8), u16, 6) + saved_arg5;
        FIELD(FIELD(obj, void *, 8), s16, 0xA) =
            FIELD(FIELD(saved_arg0, void *, 8), u16, 0xA) + saved_arg6 - 40;

        tail = (u8 *)obj + 0x20;
        FIELD(tail, u16, 0x42) = FIELD(FIELD(saved_arg0, void *, 8), u16, 2);
        FIELD(tail, u16, 0x44) = FIELD(FIELD(saved_arg0, void *, 8), u16, 6);
        ASM_SCHED_BARRIER();
        FIELD(tail, u16, 0x46) = FIELD(FIELD(saved_arg0, void *, 8), u16, 0xA);

        narrowed_arg3 = (s16)saved_arg3;
        divisor = narrowed_arg3;
        numerator_x = -(saved_arg4 << 16);
        if (narrowed_arg3 < 0) {
            divisor = narrowed_arg3 + 7;
        }
        divisor >>= 3;

        quotient_x = numerator_x / divisor;
        FIELD(tail, s32, 0x4C) = quotient_x / 2;
        ASM_KEEP(quotient_x);
        numerator_y = -(saved_arg5 << 16);
        quotient_y = numerator_y / divisor;
        FIELD(tail, s32, 0x50) = quotient_y / 2;
        ASM_KEEP(quotient_y);
        quotient_z = -(saved_arg6 << 16) / divisor;
        FIELD(tail, s32, 0x54) = quotient_z / 2;
        ASM_KEEP(quotient_z);

        rounded_x = quotient_x;
        ASM_KEEP(rounded_x);
        if (rounded_x < 0) {
            rounded_x += 3;
        }
        FIELD(tail, s32, 0x58) = rounded_x >> 2;

        rounded_y = quotient_y;
        if (rounded_y < 0) {
            rounded_y += 3;
        }
        FIELD(tail, s32, 0x5C) = rounded_y >> 2;

        rounded_z = quotient_z;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        FIELD(tail, s32, 0x60) = rounded_z >> 2;

        FIELD(tail, s16, 0x32) = saved_arg3;
        func_8004491C(obj, D_80164BC4, quotient_x);
        FIELD(obj, s32, 0x20) = saved_arg1;
        FIELD(tail, s32, 8) = saved_arg1;
    }

    ASM_KEEP(saved_arg0);
    ASM_KEEP(saved_arg1);
    ASM_KEEP(saved_arg3);
    ASM_KEEP(saved_arg4);
    ASM_KEEP(saved_arg5);
    ASM_KEEP(saved_arg6);
    ASM_KEEP(obj);
    ASM_KEEP(tail);
}
