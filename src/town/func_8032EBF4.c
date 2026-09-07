/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

s8 *func_800193F4(s8 *arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg1 > 0) {
        do {
            *(arg0 + var_v1) = 0;
            var_v1 += 1;
        } while (var_v1 < arg1);
    }
    return arg0;
}

/* MECHANISM: Frameless leaf with no saved registers or stack locals.
   Byte-typed arg0 removes the scaled index word and selects sb; the original
   pointer stays live in a0 through the loop and returns in the jr delay slot. */
