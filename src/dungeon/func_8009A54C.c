#include "common.h"

extern s8 D_800E2970[0x14];

s32 func_8009FCAC(s16 arg0) {
    s32 value;

    value = 0;
    if (arg0 >= 0) {
        register s8 *entry ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */

        value = (s32)&D_800E2970;
        entry = (s8 *)value + arg0 * 0x14;
        value = *(s16 *)(entry + 0xA);
        if (value == 0) {
            return 0;
        }
        value = *(s32 *)(entry + 0x10);
    }
    return value;
}

/* MECHANISM: Frameless leaf; one guarded $v0 carrier spans zero, global base,
   halfword condition, and result, while a guarded $v1 holds the entry.
   Assigning the halfword before the literal-zero guard preserves both zero delay slots. */
