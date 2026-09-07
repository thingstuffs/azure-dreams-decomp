#include "common.h"

extern void func_800B8A38(void);
extern s8 D_800133E7[9];

void func_800B89C4(s32 arg0, s32 arg1)
{
    register s32 raw ASM_REG("$6") = arg1;
    register s32 value ASM_REG("$5") = arg1;
    register s32 common_index ASM_REG("$3");
    register s32 small_index ASM_REG("$2");

    ASM_KEEP(value);
    value = (s16)value;
    common_index = arg0;
    if (value <= 0) {
        goto common;
    }
    if (value < 4) {
        goto small;
    }
    if (value >= 42) {
        goto common;
    }
    if (value >= 37) {
        goto special;
    }

common:
    {
        register u8 *base ASM_REG("$2") = (u8 *)0x80010000;
        u8 previous;

        ASM_KEEP(base);
        common_index = (s16)common_index * 2;
        ASM_KEEP(common_index);
        base[0x33A5 + common_index] = (u8)raw;
        previous = base[0x360A];
        base[0x360A] = (u8)raw;
        base[0x360B] = previous;
        func_800B8A38();
        return;
    }

small:
    {
        register u8 *base ASM_REG("$3") = (u8 *)0x80010000;

        small_index = arg0 << 16;
        ASM_KEEP(base);
        small_index >>= 15;
        base[0x33A5 + small_index] = (u8)raw;
        func_800B8A38();
        return;
    }

special:
    ASM_KEEP(raw);
    ASM_KEEP(value);
    D_800133E7[0] = (u8)raw;
}

/* MECHANISM: Frameless CFG pins raw arg1/signed arg1/common index to
   a2/a1/v1 while leaving the small-path v0 shift naturally delay-filled.
   Path-local v0/v1 page bases shape the full and small sibcall stores. */
