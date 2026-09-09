#include "common.h"

typedef struct S_800C8ABC_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800C8ABC_0;   /* held_arg0 in func_800C8ABC */



extern s32 func_800A48F0();
extern s32 func_800A6D30();
extern s32 func_800C8408();

s32 func_800C8ABC(void *arg0, s16 arg1, s8 arg2)
{
    S_800C8ABC_0 *held_arg0 = arg0;
    s16 held_arg1 = arg1;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 held_arg2 = arg2;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 divisor ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 remainder ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    u8 temp_v1;

    if (func_800C8408() != 0) {
        return 0;
    }
    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    temp_a0 = func_800A6D30() & 0xFFFF;
    temp_v1 = held_arg0->unk_03;
    if (temp_v1 != 0) {
        divisor = temp_v1;
        ASM_USE(divisor);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        remainder = temp_a0 % divisor;
           /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    } else {
        remainder = 0;
    }
    divisor = held_arg1 / 2;
       /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if ((remainder < divisor) || (held_arg1 == 0xFF)) {
        if ((s16)func_800A48F0(held_arg0, 1, held_arg2) >= 0) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: Pin the three live arguments to retail's s0/s1/s2 roles so the
   0x20 frame and save order match; defer their guarded keeps past the opening
   call for the s2 delay move, and reuse the v0 divisor carrier for arg1/2. */
