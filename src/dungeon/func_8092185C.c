#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800E3548;

s32 func_8092185C(void) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    u8 *var_v0;
    u8 *var_v1;

    var_a0 = 0x3F;
    var_a2 = 0x12;
    var_a1 = 1;
    var_v0 = (u8 *)&D_800E3548;
    var_v1 = var_v0 + 0xFC;
loop_1:
    if ((var_v1[1] != var_a2) || (var_v1[0] != var_a1)) {
        var_a0 -= 1;
        var_v1 -= 4;
        if (var_a0 < 0) {
            var_v0 = (u8 *)1;
        } else {
            goto loop_1;
        }
    } else {
        var_v0 = (u8 *)0;
    }
    return (s32)var_v0;
}
