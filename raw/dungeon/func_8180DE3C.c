#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80026E78() __attribute__((noreturn));
extern s32 D_800814A0[3];

void func_80026E3C(void *arg0, M2C_UNK arg1, void *arg2)
{
    register u16 temp_a0 ASM_REG("$4");
    u16 temp_v0;
    u16 temp_v0_3;
    u32 temp_v0_2;
    register s32 temp_v1 ASM_REG("$3");

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x68) + 1;
    M2C_FIELD(arg0, u16 *, 0x68) = temp_v0;
    if (temp_v0 & 1) {
        M2C_FIELD(arg2, s8 *, 0xE) = M2C_FIELD(arg0, u8 *, 0x6A);
        func_80026E78(arg0);
        return;
    }
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x6A) >> 3;
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_v0_2;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_v0_2;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_v0_2;
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x6A);
    temp_v1 = (s16)temp_v0_3 >> 4;
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x66);
    ASM_KEEP(temp_a0);
    ASM_KEEP(temp_v1);
    temp_v0_3 -= temp_v1;
    ASM_KEEP(temp_v0_3);
    temp_a0--;
    M2C_FIELD(arg0, u16 *, 0x66) = temp_a0;
    M2C_FIELD(arg0, u16 *, 0x6A) = temp_v0_3;
    if ((temp_a0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) =
            (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}

/* MECHANISM: The frameless noreturn CFG holds arg0 in a1 and keeps the odd-path store in the tail-j slot.
   Pinning the signed-shift helper to v1 and the timer to a0 leaves the adjusted value naturally in v0.
   ASM_KEEP after subu enforces subu-before-decrement while preserving the value store in the branch slot. */
