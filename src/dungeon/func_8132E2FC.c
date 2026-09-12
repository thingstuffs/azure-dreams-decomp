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

/* Creates an offset object and initializes its source position and motion parameters. */
void func_801652FC(
    void *source, s32 initial_value, s32 duration, s32 offset_x,
    s32 offset_y, s32 offset_z)
{
    S_801652FC_2 *source_obj = source;
    s32 saved_value = initial_value;
    register s32 saved_duration ASM_REG("$22") = duration;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 saved_offset_x = offset_x;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 saved_offset_y = offset_y;
    s32 saved_offset_z = offset_z;
    register void *object ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *state;
    register s32 duration_s16;
    register s32 divisor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 numerator_x;
    s32 quotient_x;
    register s32 quotient_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 quotient_z;
    s32 rounded_x;
    s32 rounded_z;

    object = func_8003FD64(0x211, source_obj);
    if (object != 0) {
        ((S_801652FC_1 *)object)->unk_10 = D_80165164;

        ((S_801652FC_3 *)(((S_801652FC_1 *)object)->unk_08))->unk_02 =
            ((S_801652FC_4 *)(source_obj->unk_08))->unk_02 + saved_offset_x;
        ((S_801652FC_3 *)(((S_801652FC_1 *)object)->unk_08))->unk_06 =
            ((S_801652FC_4 *)(source_obj->unk_08))->unk_06 + saved_offset_y;
        ((S_801652FC_3 *)(((S_801652FC_1 *)object)->unk_08))->unk_0A =
            ((S_801652FC_4 *)(source_obj->unk_08))->unk_0A + saved_offset_z - 40;

        state = (u8 *)object + 0x20;
        ((S_801652FC_0 *)state)->unk_42 = ((S_801652FC_4 *)(source_obj->unk_08))->unk_02;
        ((S_801652FC_0 *)state)->unk_44 = ((S_801652FC_4 *)(source_obj->unk_08))->unk_06;
        ((S_801652FC_0 *)state)->unk_46 = ((S_801652FC_4 *)(source_obj->unk_08))->unk_0A;

        duration_s16 = (s16)saved_duration;
        divisor = duration_s16;
        numerator_x = -(saved_offset_x << 16);
        if (duration_s16 < 0) {
            divisor = duration_s16 + 7;
        }
        divisor >>= 3;

        quotient_x = numerator_x / divisor;
        ((S_801652FC_0 *)state)->unk_4C = quotient_x / 2;
        ASM_KEEP(quotient_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        duration = -(saved_offset_y << 16);
        quotient_y = duration / divisor;
        ((S_801652FC_0 *)state)->unk_50 = quotient_y / 2;
        ASM_KEEP(quotient_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        quotient_z = -(saved_offset_z << 16) / divisor;
        ((S_801652FC_0 *)state)->unk_54 = quotient_z / 2;

        rounded_x = quotient_x;
        ASM_KEEP(rounded_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (rounded_x < 0) {
            rounded_x += 3;
        }
        ((S_801652FC_0 *)state)->unk_58 = rounded_x >> 2;

        rounded_z = quotient_y;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        ((S_801652FC_0 *)state)->unk_5C = rounded_z >> 2;

        rounded_z = quotient_z;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        ((S_801652FC_0 *)state)->unk_60 = rounded_z >> 2;

        ((S_801652FC_0 *)state)->unk_32 = saved_duration;
        func_8004491C(object, D_80164BC4, quotient_x);
        ((S_801652FC_1 *)object)->unk_20 = saved_value;
        ((S_801652FC_0 *)state)->unk_08 = saved_value;
    }

    ASM_KEEP(saved_duration);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_offset_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
}
