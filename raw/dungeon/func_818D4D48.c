#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern s16 D_80025118;
extern s32 D_800814A0[3];

void func_818D4D48(void *arg0, M2C_UNK arg1, void *arg2)
{
    void *held_arg0 = arg0;
    u16 temp_a0;
    u16 temp_count;
    u16 temp_v1;

    temp_count = M2C_FIELD(held_arg0, u16 *, 2);
    D_80025118 = 1;
    M2C_FIELD(held_arg0, u16 *, 2) = (u16)(temp_count - 1);

    M2C_FIELD(arg2, u8 *, 0xC) = (u8)((M2C_FIELD(arg2, u8 *, 0xC) * 0xA) / 13);
    M2C_FIELD(arg2, u8 *, 0xD) = (u8)((M2C_FIELD(arg2, u8 *, 0xD) * 0xA) / 13);
    M2C_FIELD(arg2, u8 *, 0xE) = (u8)((M2C_FIELD(arg2, u8 *, 0xE) * 0xA) / 13);

    temp_a0 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_v1 = temp_a0 + 0x300;
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v1;

    if ((u32)(temp_v1 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1A) = (u16)(temp_a0 - 0xD00);
    }

    if ((s16)M2C_FIELD(held_arg0, u16 *, 2) <= 0) {
        M2C_FIELD(held_arg0, u16 *, -2) = (u16)(M2C_FIELD(held_arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }

    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(held_arg0, u16 *, -2) = (u16)(M2C_FIELD(held_arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
    
}

/* MECHANISM: The frameless leaf uses only its compiler-required 0x10 scratch frame and holds
   arg0 in a3 for the full tail. Splitting the count RMW around D_80025118's store keeps the
   global page in a0 and the division magic in a1, reproducing retail's early schedule. */
