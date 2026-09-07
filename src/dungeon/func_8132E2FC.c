/* row func_8132E2FC, true base 0x801652FC -- exemplar-seeded from landed
 * func_80BC1528 (MATCH @2.7.2-cdk-G0, gate_verified). Opcode-sequence
 * similarity 0.9843. Ordinary code: no symbol alias, no .text section
 * attribute, no literal word arrays, first word is the prologue.
 *
 * Adaptation measured off the retail stream:
 *   - one fewer parameter (exemplar's arg2 is gone; the value stored at
 *     obj+0x20 / tail+8 is arg1 here), so every later arg shifts one slot
 *   - `((S_801652FC_0 *)tail)->unk_14 = arg1` is absent
 *   - the six vector fields sit 0xC higher (0x36->0x42 ... 0x54->0x60)
 *   - the z bias is -40, not -100
 *   - the two overlay data symbols are this image's
 */
#include "common.h"

typedef struct S_801652FC_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0xE];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u8 pad_48[0x4];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_801652FC_0;   /* tail in func_801652FC */

typedef struct S_801652FC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_801652FC_1;   /* obj in func_801652FC */

typedef struct S_801652FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801652FC_2;   /* saved_arg0 in func_801652FC */

typedef struct S_801652FC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_801652FC_3;   /* ((S_801652FC_1 *)obj)->unk_08 in func_801652FC */

typedef struct S_801652FC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801652FC_4;   /* ((S_801652FC_2 *)saved_arg0)->unk_08 in func_801652FC */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C();
extern u8 D_80164BC4[];
extern u8 D_80165164[];

void func_801652FC(
    void *arg0, s32 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5)
{
    S_801652FC_2 *saved_arg0 = arg0;
    s32 saved_arg1 = arg1;
    register s32 saved_arg3 ASM_REG("$22") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 saved_arg4 ASM_REG("$19") = arg3;   /* MATCH pin: load-bearing for the whole function shape */
    s32 saved_arg5 = arg4;
    s32 saved_arg6 = arg5;
    register void *obj ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *tail;
    register s32 narrowed_arg3;
    register s32 divisor ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 numerator_x;
    register s32 numerator_y ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 quotient_x;
    register s32 quotient_y ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 quotient_z;
    s32 rounded_x;
    register s32 rounded_y ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 rounded_z;

    obj = func_8003FD64(0x211, saved_arg0);
    if (obj != 0) {
        ((S_801652FC_1 *)obj)->unk_10 = D_80165164;

        ((S_801652FC_3 *)(((S_801652FC_1 *)obj)->unk_08))->unk_02 =
            ((S_801652FC_4 *)(saved_arg0->unk_08))->unk_02 + saved_arg4;
        ((S_801652FC_3 *)(((S_801652FC_1 *)obj)->unk_08))->unk_06 =
            ((S_801652FC_4 *)(saved_arg0->unk_08))->unk_06 + saved_arg5;
        ((S_801652FC_3 *)(((S_801652FC_1 *)obj)->unk_08))->unk_0A =
            ((S_801652FC_4 *)(saved_arg0->unk_08))->unk_0A + saved_arg6 - 40;

        tail = (u8 *)obj + 0x20;
        ((S_801652FC_0 *)tail)->unk_42 = ((S_801652FC_4 *)(saved_arg0->unk_08))->unk_02;
        ((S_801652FC_0 *)tail)->unk_44 = ((S_801652FC_4 *)(saved_arg0->unk_08))->unk_06;
        ((S_801652FC_0 *)tail)->unk_46 = ((S_801652FC_4 *)(saved_arg0->unk_08))->unk_0A;

        narrowed_arg3 = (s16)saved_arg3;
        divisor = narrowed_arg3;
        numerator_x = -(saved_arg4 << 16);
        if (narrowed_arg3 < 0) {
            divisor = narrowed_arg3 + 7;
        }
        divisor >>= 3;

        quotient_x = numerator_x / divisor;
        ((S_801652FC_0 *)tail)->unk_4C = quotient_x / 2;
        ASM_KEEP(quotient_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        numerator_y = -(saved_arg5 << 16);
        quotient_y = numerator_y / divisor;
        ((S_801652FC_0 *)tail)->unk_50 = quotient_y / 2;
        ASM_KEEP(quotient_y);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        quotient_z = -(saved_arg6 << 16) / divisor;
        ((S_801652FC_0 *)tail)->unk_54 = quotient_z / 2;

        rounded_x = quotient_x;
        ASM_KEEP(rounded_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (rounded_x < 0) {
            rounded_x += 3;
        }
        ((S_801652FC_0 *)tail)->unk_58 = rounded_x >> 2;

        rounded_y = quotient_y;
        if (rounded_y < 0) {
            rounded_y += 3;
        }
        ((S_801652FC_0 *)tail)->unk_5C = rounded_y >> 2;

        rounded_z = quotient_z;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        ((S_801652FC_0 *)tail)->unk_60 = rounded_z >> 2;

        ((S_801652FC_0 *)tail)->unk_32 = saved_arg3;
        func_8004491C(obj, D_80164BC4, quotient_x);
        ((S_801652FC_1 *)obj)->unk_20 = saved_arg1;
        ((S_801652FC_0 *)tail)->unk_08 = saved_arg1;
    }

    ASM_KEEP(saved_arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(saved_arg4);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
}
