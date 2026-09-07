#include "common.h"

#define FIELD(x, type, off) (*(type *)((u8 *)(x) + (off)))

extern void func_80172A0C(void) __attribute__((noreturn));
extern s32 D_800814A0;
extern u8 D_80174C8C[];
extern s32 D_80174CE0;

void func_80172874(void *arg0, void *arg1, void *arg2)
{
    register void *base ASM_REG("$7") = arg0;
    register void *source ASM_REG("$8");
    register void *owner ASM_REG("$9");
    s16 temp_a0_3;
    s16 temp_v1;
    s32 temp_lo;
    s32 temp_lo_2;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 owner_value;
    void *parent;

    parent = FIELD(base, void *, 0x20);
    source = FIELD(base, void *, 0x24);
    owner = FIELD(parent, void *, -0x14);
    temp_a0 = FIELD(arg2, u16, 0x1A);
    owner_value = FIELD(owner, u16, 6);
    temp_v0 = temp_a0 + 0x190;
    FIELD(arg2, u16, 0x1A) = temp_v0;
    FIELD(arg2, u16, 6) = owner_value;
    if ((u16)temp_v0 >= 0x1001U) {
        FIELD(arg2, u16, 0x1A) = temp_a0 - 0xE70;
    }

    temp_v1 = FIELD(base, s16, 0x12);
    temp_a0_2 = FIELD(base, volatile u16, 0x12);
    if (temp_v1 == 1) {
        goto mode_one;
    }
    if (temp_v1 < 2) {
        if (temp_v1 != 0) {
            func_80172A0C();
        }
        goto mode_zero;
    }
    if (temp_v1 != 2) {
        func_80172A0C();
    }
    goto mode_two;

mode_zero:
    temp_v1_2 = FIELD(base, u16, 0x16) + 1;
    temp_a0_3 = FIELD(base, s16, 0x18);
    temp_lo = ((s32)(temp_v1_2 << 16) >> 9) / temp_a0_3;
    FIELD(base, u16, 0x16) = temp_v1_2;
    FIELD(arg2, s8, 0xC) = temp_lo;
    FIELD(arg2, s8, 0xD) = temp_lo;
    FIELD(arg2, s8, 0xE) = temp_lo;
    if (FIELD(base, s16, 0x16) >= 5) {
        FIELD(base, u16, 0x12) = FIELD(base, u16, 0x12) + 1;
        func_80172A0C();
    }
    goto done;

mode_one:
    {
    register u32 flag_base ASM_REG("$2");
    flag_base = 0x80170000;
    ASM_KEEP(flag_base);
    if (FIELD(flag_base, s32, 0x4CE0) == 0) {
        FIELD(base, s16, 0x12) = temp_a0_2 + 1;
        FIELD(base, s16, 0x18) = 0x14;
        FIELD(base, u16, 0x16) = 0x14;
    }
    if (FIELD(owner, void *, 0x2C) == D_80174C8C) {
        FIELD(base, s16, 0x18) = 0x14;
        FIELD(base, u16, 0x16) = 0x14;
        FIELD(base, s16, 0x12) = FIELD(base, u16, 0x12) + 1;
    }
    FIELD(arg1, s32, 0) = FIELD(source, s32, 0);
    FIELD(arg1, s32, 4) = FIELD(source, s32, 4);
    FIELD(arg1, s32, 8) = FIELD(source, s32, 8);
    func_80172A0C();
    }

mode_two:
    temp_v1_3 = FIELD(base, u16, 0x16) - 1;
    temp_lo_2 = ((s32)(temp_v1_3 << 16) >> 9) / FIELD(base, s16, 0x18);
    FIELD(base, u16, 0x16) = temp_v1_3;
    FIELD(arg2, s8, 0xC) = temp_lo_2;
    FIELD(arg2, s8, 0xD) = temp_lo_2;
    FIELD(arg2, s8, 0xE) = temp_lo_2;
    if (FIELD(base, s16, 0x16) <= 0) {
        register s32 *global_base ASM_REG("$3");
        global_base = (s32 *)0x80080000;
        ASM_KEEP(global_base);
        FIELD(base, u16, -2) |= 0x8000;
        FIELD(global_base, s32, 0x14A0) |= 0x8000;
    }

done:
    return;
}
