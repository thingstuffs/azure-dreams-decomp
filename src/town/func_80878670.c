#include "common.h"

extern s32 *D_807030A4[];

void func_80702670(s32 arg0) {
    s32 value = arg0;
    s32 temp_v1;
    register s32 temp_a0 ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 base;

    if (value != 0) {
        temp_v1 = value;
        if (value < 0) {
            temp_v1 = value + 31;
        }
        temp_v1 >>= 5;
        temp_a0 = temp_v1 << 2;
        temp_v1 <<= 5;
        temp_a0 += (base = (s32)D_807030A4[0],
                    temp_v1 = value - temp_v1, base);
        base = 1;
        value = *(s32 *)temp_a0;
        base <<= temp_v1;
        base |= value;
        *(s32 *)temp_a0 = base;
    }
}

/* MECHANISM: Frameless leaf with guarded roles a1=input/load, v1=quotient/remainder,
   a0=word offset/pointer, and v0=base/mask/result. The comma sequence exposes
   lw-global; subu; addu, filling the load delay and preserving retail order. */
