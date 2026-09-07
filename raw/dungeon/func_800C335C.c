#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800A48F0();
extern s32 func_800A6D30();
extern s32 func_800C8408();
extern s32 func_800C8B1C();

s32 func_800C8ABC(void *arg0, s16 arg1, s8 arg2)
{
    register void *held_arg0 ASM_REG("$16") = arg0;
    register s16 held_arg1 ASM_REG("$17") = arg1;
    register s8 held_arg2 ASM_REG("$18") = arg2;
    register s32 temp_a0 ASM_REG("$4");
    register s32 divisor ASM_REG("$2");
    register s32 remainder ASM_REG("$3");
    u8 temp_v1;

    if (func_800C8408() != 0) {
        return 0;
    }
    ASM_KEEP(held_arg0);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);

    temp_a0 = func_800A6D30() & 0xFFFF;
    temp_v1 = FIELD(held_arg0, u8, 3);
    if (temp_v1 != 0) {
        divisor = temp_v1;
        ASM_USE(divisor);
        remainder = temp_a0 % divisor;
        ASM_KEEP(remainder);
        func_800C8B1C();
        return (u32)held_arg1 << 16;
    }

    remainder = 0;
    ASM_KEEP(remainder);
    divisor = held_arg1 / 2;
    ASM_USE(divisor);
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
