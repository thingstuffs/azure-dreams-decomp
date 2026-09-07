#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();

extern u8 D_80024EE0[];
extern u8 D_80025854[];
extern u8 D_80045C34[];
extern u16 D_800257CC;

void *func_80024FD8(void *arg0, s16 arg1, s16 arg2)
{
    register s32 temp_a0 ASM_REG("$4");
    s32 value;
    u16 counter;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    register void *temp_v1_2 ASM_REG("$3");

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != 0) {
        FIELD(temp_v0, void *, 0x10) = D_80024EE0;
        func_8004491C(temp_v0, D_80045C34);
        temp_v1 = FIELD(temp_v0, void *, 8);
        FIELD(temp_v1, u16, 2) = FIELD(arg0, u16, 2);
        FIELD(temp_v1, u16, 6) = FIELD(arg0, u16, 6);
        FIELD(temp_v1, u16, 0xA) = FIELD(arg0, u16, 0xA);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0, s32, 0xC) = 0x808080;
        FIELD(temp_s0, s16, 0x1C) = 0x400;
        FIELD(temp_s0, s16, 0x1E) = 0x1CCC;
        func_8003DB94(temp_s0, D_80025854, 0);
        temp_a0 = (s16)arg2;
        ASM_KEEP(temp_a0);
        FIELD(temp_s0, s16, 0x18) = (temp_a0 << 8) - 0x400;
        value = 0x60;
        ASM_KEEP(value);
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        ASM_KEEP(temp_v1_2);
        FIELD(temp_s0, s16, 0x10) = value;
        counter = D_800257CC;
        FIELD(temp_s0, s16, 0x16) = 0x400;
        FIELD(temp_v1_2, s16, 0x24) = arg2;
        FIELD(temp_v1_2, s16, 0x14) = arg1;
        FIELD(temp_v1_2, s16, 0x1E) = temp_a0 * 2;
        D_800257CC = counter + 1;
    }
    return temp_v0;
}

/* MECHANISM: Natural argument liveness preserves the retail 0x28 frame and s0-s4 save contract.
   The guarded a0/v1 roles share one signed arg2 conversion and hold the three-store destination base.
   An unpinned 0x60 local plus ordered keeps yields the exact li/addiu/lui/sh/lhu counter schedule. */
