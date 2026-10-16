#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80003C1C(u16);                         /* extern */

void func_80003814(void) {
    u16 temp_a0;
    void *var_s0;

    var_s0 = (void *)4;
    do {
        func_80003C1C(M2C_FIELD(var_s0, u16 *, 0x3F58));
        temp_a0 = M2C_FIELD(var_s0, u16 *, 0x3F5A);
        var_s0 += 4;
        func_80003C1C(temp_a0);
    } while ((s32) var_s0 < 0x10);
}
