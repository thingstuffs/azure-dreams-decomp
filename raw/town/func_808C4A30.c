#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80000B90(u16);                         /* extern */

void func_80000A30(void) {
    u16 temp_a0;
    void *var_s0;

    var_s0 = (void *)4;
    do {
        func_80000B90(M2C_FIELD(var_s0, u16 *, 0xDA4));
        temp_a0 = M2C_FIELD(var_s0, u16 *, 0xDA6);
        var_s0 += 4;
        func_80000B90(temp_a0);
    } while ((s32) var_s0 < 8);
}
