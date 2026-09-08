#include "common.h"

extern s8 D_800133E7[9];

void func_800B89C4(s32 arg0, s32 arg1)
{
    s32 raw = arg1;
    register s32 value ASM_REG("$5") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    s32 common_index;
    s32 small_index;

    ASM_KEEP(value);   /* MATCH pin: retail register colouring depends on it */
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
        register u8 *base ASM_REG("$2") = (u8 *)0x80010000;   /* MATCH pin: keeps a constant in a register as retail does */
        u8 previous;

        ASM_KEEP(base);   /* MATCH pin: keeps a constant in a register as retail does */
        common_index = (s16)common_index * 2;
        base[0x33A5 + common_index] = (u8)raw;
        previous = base[0x360A];
        base[0x360A] = (u8)raw;
        base[0x360B] = previous;
        return;
    }

small:
    {
        u8 *base = (u8 *)0x80010000;

        small_index = arg0 << 16;
        ASM_KEEP(base);   /* MATCH pin: keeps a constant in a register as retail does */
        small_index >>= 15;
        base[0x33A5 + small_index] = (u8)raw;
        return;
    }

special:
    ASM_KEEP(value);   /* MATCH pin: retail register colouring depends on it */
    D_800133E7[0] = (u8)raw;
}

/* MECHANISM: Frameless CFG pins raw arg1/signed arg1/common index to
   a2/a1/v1 while leaving the small-path v0 shift naturally delay-filled.
   Path-local v0/v1 page bases shape the full and small sibcall stores. */
