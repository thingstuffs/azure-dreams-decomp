#include "common.h"

extern s32 func_800A9B24();

s32 func_800A9ADC(s32 arg0, u8 *arg1) {
    register s32 result ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 kind;

    kind = arg1[1];

    if (kind == 13) {
        u8 value = arg1[0];

        result = 1;
        if (value != 4) {
#ifdef NON_MATCHING
            return func_800A9B24(value == 3);
#else
            result = value == 3;
            ASM_TAILSLOT_PIN_TIED(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            return func_800A9B24();
#endif
        }
    } else {
        result = 1;
        if (kind == result) {
            result = arg1[0] != 8;
        }
    }
    return result;
}

/* MECHANISM: The frameless leaf holds full-width kind in $v1 and result in $v0.
   A block-local keep materializes the else-path 1 before its branch; comparing kind
   to that held result prevents rematerialization and restores the 20-word CFG. */
