#include "common.h"

typedef struct S_80BC1528_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80BC1528_0;   /* obj in func_80BC1528 */

typedef struct S_80BC1528_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80BC1528_1;   /* saved_arg0 in func_80BC1528 */

typedef struct S_80BC1528_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x2];
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80BC1528_2;   /* tail in func_80BC1528 */

typedef struct S_80BC1528_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80BC1528_3;   /* ((S_80BC1528_0 *)obj)->unk_08 in func_80BC1528 */

typedef struct S_80BC1528_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80BC1528_4;   /* ((S_80BC1528_1 *)saved_arg0)->unk_08 in func_80BC1528 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C();
extern u8 D_80170884[];
extern u8 D_80170A64[];

void func_80BC1528(
    void *arg0, s16 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    S_80BC1528_1 *saved_arg0 = arg0;
    register s16 saved_arg1 ASM_REG("$23") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 saved_arg2 = arg2;
    register s32 saved_arg3 ASM_REG("$22") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 saved_arg4 = arg4;
    s32 saved_arg5 = arg5;
    s32 saved_arg6 = arg6;
    register void *obj ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80BC1528_2 *tail;
    register s32 narrowed_arg3;
    register s32 divisor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 numerator_x;
    register s32 numerator_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 quotient_x;
    register s32 quotient_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 quotient_z;
    s32 rounded_x;
    register s32 rounded_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 rounded_z;

    obj = func_8003FD64(0x211, saved_arg0);
    if (obj != 0) {
        ((S_80BC1528_0 *)obj)->unk_10 = D_80170A64;

        ((S_80BC1528_3 *)(((S_80BC1528_0 *)obj)->unk_08))->unk_02 =
            ((S_80BC1528_4 *)(saved_arg0->unk_08))->unk_02 + saved_arg4;
        ((S_80BC1528_3 *)(((S_80BC1528_0 *)obj)->unk_08))->unk_06 =
            ((S_80BC1528_4 *)(saved_arg0->unk_08))->unk_06 + saved_arg5;
        ((S_80BC1528_3 *)(((S_80BC1528_0 *)obj)->unk_08))->unk_0A =
            ((S_80BC1528_4 *)(saved_arg0->unk_08))->unk_0A + saved_arg6 - 100;

        tail = (u8 *)obj + 0x20;
        tail->unk_36 = ((S_80BC1528_4 *)(saved_arg0->unk_08))->unk_02;
        tail->unk_38 = ((S_80BC1528_4 *)(saved_arg0->unk_08))->unk_06;
        tail->unk_3A = ((S_80BC1528_4 *)(saved_arg0->unk_08))->unk_0A;

        narrowed_arg3 = (s16)saved_arg3;
        divisor = narrowed_arg3;
        numerator_x = -(saved_arg4 << 16);
        if (narrowed_arg3 < 0) {
            divisor = narrowed_arg3 + 7;
        }
        divisor >>= 3;

        quotient_x = numerator_x / divisor;
        tail->unk_40 = quotient_x / 2;
        ASM_KEEP(quotient_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        numerator_y = -(saved_arg5 << 16);
        quotient_y = numerator_y / divisor;
        tail->unk_44 = quotient_y / 2;
        ASM_KEEP(quotient_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        quotient_z = -(saved_arg6 << 16) / divisor;
        tail->unk_48 = quotient_z / 2;

        rounded_x = quotient_x;
        ASM_KEEP(rounded_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (rounded_x < 0) {
            rounded_x += 3;
        }
        tail->unk_4C = rounded_x >> 2;

        rounded_y = quotient_y;
        if (rounded_y < 0) {
            rounded_y += 3;
        }
        tail->unk_50 = rounded_y >> 2;

        rounded_z = quotient_z;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        tail->unk_54 = rounded_z >> 2;

        tail->unk_14 = saved_arg1;
        tail->unk_32 = saved_arg3;
        func_8004491C(obj, D_80170884, quotient_x);
        ((S_80BC1528_0 *)obj)->unk_20 = saved_arg2;
        tail->unk_08 = saved_arg2;
    }

    ASM_KEEP(saved_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg5);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg6);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
}
