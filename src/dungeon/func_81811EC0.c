#include "common.h"

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define KEEP_VALUE(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define KEEP_VALUE(value) ASM_KEEP(value)
#endif

extern u8 D_800157D2;

s32 func_80026EC0(s32 arg0, s32 arg1) {
    register s32 var_a3 ASM_REG("$7");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 var_v0;
    s32 var_v1;
    u8 *var_a2;

    var_a3 = 0;
    KEEP_VALUE(var_a3);
    var_v1 = var_a3;
    var_a2 = &D_800157D2;
loop_1:
    if (*var_a2 == arg0) {
        var_v0 = var_v1;
        if (var_a3 != arg1) {
            var_a3 += 1;
            goto block_4;
        }
    } else {
block_4:
        var_v1 += 1;
        var_a2 += 0x13;
        if (var_v1 >= 0x40) {
            var_v0 = -1;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
