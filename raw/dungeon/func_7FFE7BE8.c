#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern void func_70040A18(void *, void *);
extern void func_7003A7C4(void *, void *, s32);
extern s32 D_8004136C;
extern s32 D_800E2BB8;

void func_7FFE7BE8(void *arg0, void *arg1, void *arg2)
{
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v1;
    s32 copied_value;
    u16 flags;

    FIELD(arg0, void *, 0x44) = arg1;
    func_70040A18(arg0, &D_8004136C);
    temp_a0 = FIELD(arg0, void *, 0xC);
    FIELD(temp_a0, s16, 0x10) = 0x20;
    FIELD(temp_a0, u16, 0x14) = FIELD(temp_a0, u16, 0x14) | 0xC;
    temp_v1 = FIELD(arg0, void *, 8);
    FIELD(temp_v1, u16, 2) = FIELD(arg2, u16, 2);
    FIELD(temp_v1, u16, 6) = FIELD(arg2, u16, 6);
    FIELD(temp_v1, u16, 0xA) = FIELD(arg2, u16, 0xA);
    temp_a0_2 = FIELD(arg0, void *, 0xC);
    FIELD(temp_a0_2, s16, 0x1E) = 0x800;
    FIELD(temp_a0_2, s16, 0x1C) = 0x800;
    FIELD(arg0, s32, 0x2C) = FIELD(arg1, s32, 0xC);
    copied_value = FIELD(arg1, s32, 0xC);
    flags = FIELD(temp_a0_2, u16, 0x14);
    FIELD(temp_a0_2, s16, 0x12) = 0x7DCF;
    flags |= 0x100;
    FIELD(temp_a0_2, s32, 0xC) = copied_value;
    FIELD(temp_a0_2, u16, 0x14) = flags;
    func_7003A7C4(temp_a0_2, &D_800E2BB8, 0);
}
