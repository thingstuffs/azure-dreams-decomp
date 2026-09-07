#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80026E3C_0_pre {
    u16 unk_00;
} S_80026E3C_0_pre;   /* the 0x2 bytes before arg0 in func_80026E3C, addressed as arg0[-1] */

typedef struct S_80026E3C_0 {
    u8 pad_00[0x66];
    u16 unk_66;
    u16 unk_68;
    union { u8 u8; u16 u16; } unk_6A;   /* accessed as both */
} S_80026E3C_0;   /* arg0 in func_80026E3C */

typedef struct S_80026E3C_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80026E3C_1;   /* arg2 in func_80026E3C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80026E78() __attribute__((noreturn));
extern s32 D_800814A0[3];

void func_80026E3C(void *arg0, M2C_UNK arg1, S_80026E3C_1 *arg2)
{
    register u16 temp_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    u16 temp_v0;
    u16 temp_v0_3;
    u32 temp_v0_2;
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    temp_v0 = ((S_80026E3C_0 *)arg0)->unk_68 + 1;
    ((S_80026E3C_0 *)arg0)->unk_68 = temp_v0;
    if (temp_v0 & 1) {
        arg2->unk_0E = ((S_80026E3C_0 *)arg0)->unk_6A.u8;
        func_80026E78(arg0);
        return;
    }
    temp_v0_2 = ((S_80026E3C_0 *)arg0)->unk_6A.u16 >> 3;
    arg2->unk_0E = (s8) temp_v0_2;
    arg2->unk_0D = (s8) temp_v0_2;
    arg2->unk_0C = (s8) temp_v0_2;
    temp_v0_3 = ((S_80026E3C_0 *)arg0)->unk_6A.u16;
    temp_v1 = (s16)temp_v0_3 >> 4;
    temp_a0 = ((S_80026E3C_0 *)arg0)->unk_66;
    temp_v0_3 -= temp_v1;
    ASM_KEEP(temp_v0_3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_a0--;
    ((S_80026E3C_0 *)arg0)->unk_66 = temp_a0;
    ((S_80026E3C_0 *)arg0)->unk_6A.u16 = temp_v0_3;
    if ((temp_a0 << 0x10) <= 0) {
        ((S_80026E3C_0_pre *)arg0)[-1].unk_00 =
            (u16)(((S_80026E3C_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}

/* MECHANISM: The frameless noreturn CFG holds arg0 in a1 and keeps the odd-path store in the tail-j slot.
   Pinning the signed-shift helper to v1 and the timer to a0 leaves the adjusted value naturally in v0.
   ASM_KEEP after subu enforces subu-before-decrement while preserving the value store in the branch slot. */
