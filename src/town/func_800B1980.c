#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E99C();                         /* extern */

void func_800AF0E0(s32 arg0, s32 arg1) {
    s32 **var_s1;
    s32 *temp_v0;
    s32 temp_a1;
    s32 var_s0;

    var_s0 = 0x14;
    arg1 += 0x14;
    if (var_s0 < arg1) {
        temp_a1 = arg1;
        var_s1 = arg0 + 0x50;
        do {
            temp_v0 = *var_s1;
            var_s1 += 1;
            var_s0 += 1;
            func_8004E99C(*temp_v0);
        } while (var_s0 < temp_a1);
    }
}

/* MECHANISM: A 0x20 frame follows from the three held loop values: s0 index,
   s2 bound, and s1 cursor. Updating a1 before the guard then copying it after
   the edge emits the retail save order and move; unit pointer stride gives +4. */
