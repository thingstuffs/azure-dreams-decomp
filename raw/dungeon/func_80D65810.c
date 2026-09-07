#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_800DE870[];
extern void func_80045340(void);
extern void func_80170D34(void);

void func_80D65810(s32 arg0, void *arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5) {
    u16 temp_v0_2;
    void *input;
    u16 x;
    register s32 y ASM_REG("$20");
    register s32 z ASM_REG("$21");
    register s32 size ASM_REG("$2");
    void *temp_a0;
    void *temp_a0_2;
    register void *temp_s0 ASM_REG("$16");
    register void *temp_s1 ASM_REG("$17");
    void *temp_v0;

    input = arg1;
    x = arg3;
    y = arg4;
    z = arg5;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s16 *, 0xC) = 0x1E;
        M2C_FIELD(temp_s0, s16 *, 0xE) = 0x1E;
        M2C_FIELD(temp_v0, void **, 0x10) = func_80170D34;
        func_8004491C(temp_v0, func_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 6) = 0;
        M2C_FIELD(temp_a0, u16 *, 0x14) |= 0xC;
        ASM_SCHED_BARRIER();
        temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 0x14);
        ASM_KEEP(temp_v0_2);
        size = 0x60;
        ASM_KEEP(size);
        M2C_FIELD(temp_a0, s16 *, 0x10) = size;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16)(temp_v0_2 | 2);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, u16 *, 2) = x;
        M2C_FIELD(temp_s1, u16 *, 6) = (u16)y;
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16)z;
        M2C_FIELD(temp_s0, s32 *, 0x34) = 0x40000;
        M2C_FIELD(temp_s0, s32 *, 0x40) = 0x8000;
        M2C_FIELD(temp_s0, s32 *, 0x2C) = (s32)((s32)M2C_FIELD(temp_s1, s32 *, 0) >> 1);
        M2C_FIELD(temp_s0, s32 *, 0x30) = (s32)((s32)M2C_FIELD(temp_s1, s32 *, 4) >> 1);
        if (M2C_FIELD(temp_s0, s32 *, 0x2C) == 0) {
            M2C_FIELD(temp_s0, s32 *, 0x2C) = (s32)(((rand(temp_a0) & 0x1F) - 0x10) << 0xF);
            M2C_FIELD(temp_s0, s32 *, 0x30) = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
        }
        M2C_FIELD(temp_s0, s32 *, 0x38) = (s32)(0 - ((s32)M2C_FIELD(temp_s0, s32 *, 0x2C) >> 4));
        M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32)(0 - ((s32)M2C_FIELD(temp_s0, s32 *, 0x30) >> 4));
        M2C_FIELD(temp_s1, u16 *, 2) = (u16)(M2C_FIELD(temp_s1, u16 *, 2) + M2C_FIELD(input, u16 *, 2));
        M2C_FIELD(temp_s1, u16 *, 6) = (u16)(M2C_FIELD(temp_s1, u16 *, 6) + M2C_FIELD(input, u16 *, 6));
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16)(M2C_FIELD(temp_s1, u16 *, 0xA) + M2C_FIELD(input, u16 *, 0xA));
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0xC00;
        M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0xC00;
        M2C_FIELD(temp_a0_2, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0_2, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_a0_2, u16 *, 0x14) = (u16)(M2C_FIELD(temp_a0_2, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_a0_2, D_800DE870, 0);
    }
}

/* MECHANISM: Inherited pins preserve the retail 0x30 frame and s4/s5 argument holds.
   Splitting the flags RMW around ASM_SCHED_BARRIER makes its sh precede the reused-value copy.
   Guarded s0/s1 pins restore the held object/subobject bases perturbed by that zero-word fence. */
