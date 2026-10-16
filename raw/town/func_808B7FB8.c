#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80003720(s32);                         /* extern */
s32 func_80003C70(u16);                             /* extern */

void func_800037B8(void) {
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = NULL;
loop_1:
    var_s0 += 4;
    if (func_80003C70(M2C_FIELD(var_s0, u16 *, 0x3F88)) != 0) {
        var_s1 += 1;
        goto loop_1;
    }
    func_80003720(var_s1);
}
