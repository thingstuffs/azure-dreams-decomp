#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A6620();          /* extern */
extern M2C_UNK D_80010248;

typedef struct S_800F6514_0 {
    u8 unk_00;
    u8 unk_01;
} S_800F6514_0;   /* var_s0 in func_800F6514 */

void func_800F6514(void) {
    M2C_UNK *var_s0;
    s32 var_s1;

    var_s0 = (M2C_UNK *) 0x80010248;
    var_s1 = 0;
    do {
        if ((((S_800F6514_0 *)var_s0)->unk_01 == 0x13) && (((S_800F6514_0 *)var_s0)->unk_00 == 2)) {
            func_800A6620(var_s0, 1);
        }
        var_s1 += 1;
        var_s0 += 1;
    } while (var_s1 < 0x14);
}

/* MECHANISM: A fixed-address pointer literal forces retail's lui/ori base construction.
   Advancing one M2C_UNK element gives the four-byte loop stride while preserving
   the seed's 0x28 frame, saved-register hold set, and delay-slot CFG. */
