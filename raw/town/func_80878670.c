#include "common.h"

extern s32 *D_807030A4[];

void func_80702670(s32 arg0) {
    register s32 value ASM_REG("$5") = arg0;
    register s32 temp_v1 ASM_REG("$3");
    register s32 temp_a0 ASM_REG("$4");
    register s32 base ASM_REG("$2");

    if (value != 0) {
        temp_v1 = value;
        if (value < 0) {
            temp_v1 = value + 31;
        }
        temp_v1 >>= 5;
        ASM_KEEP(temp_v1);
        temp_a0 = temp_v1 << 2;
        ASM_KEEP(temp_a0);
        temp_v1 <<= 5;
        ASM_KEEP(temp_v1);
        temp_a0 += (base = (s32)D_807030A4[0],
                    temp_v1 = value - temp_v1, base);
        ASM_KEEP(value);
        ASM_KEEP(temp_v1);
        ASM_KEEP(base);
        ASM_KEEP(temp_a0);
        base = 1;
        value = *(s32 *)temp_a0;
        base <<= temp_v1;
        base |= value;
        *(s32 *)temp_a0 = base;
        ASM_KEEP(value);
        ASM_KEEP(base);
    }
}

/* MECHANISM: Frameless leaf with guarded roles a1=input/load, v1=quotient/remainder,
   a0=word offset/pointer, and v0=base/mask/result. The comma sequence exposes
   lw-global; subu; addu, filling the load delay and preserving retail order. */
