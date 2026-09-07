#include "common.h"

extern s8 D_80016000[];

s32 func_8001ADE0(s32 arg0) {
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");
    register s32 *temp_a1 ASM_REG("$5");
    s32 result;

    if (arg0 != 0) {
        if (arg0 != 1) {
            temp_v1 = *(s32 *)D_80016000;
            temp_v0 = arg0;
            if (arg0 < 0) {
                temp_v0 = arg0 + 31;
            }
            temp_v0 >>= 5;
            temp_v1 = *(s32 *)(temp_v1 + 0x18);
            temp_v0 <<= 2;
            temp_a1 = (s32 *)(temp_v0 + temp_v1);

            temp_v0 = arg0;
            if (arg0 < 0) {
                temp_v0 = arg0 + 31;
            }
            temp_v0 >>= 5;
            temp_v0 <<= 5;
            temp_v0 = arg0 - temp_v0;
            temp_v1 = 1;
            ASM_KEEP(temp_v0);
            temp_v1 <<= temp_v0;
            ASM_KEEP(temp_v1);
            ASM_KEEP(temp_a1);
            result = temp_v1 & *temp_a1;
        } else {
            result = 1;
        }
    } else {
        result = 0;
    }
    return result;
}

/* MECHANISM: Define the row at its true-space identity and keep it a frameless leaf;
   the apparent jumps to 0x8001AE48 are local return joins, not calls.
   Guarded site-map roles reuse v0 for both signed quotient phases, v1 for the
   loaded base then bit mask, and a1 for the selected word address. */
