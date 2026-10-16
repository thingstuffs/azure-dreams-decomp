#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700C28(u16);                         /* extern */

void func_80700AD4(void) {
    s32 var_s0;
    u16 temp_a0;

    var_s0 = 4;
    do {
        func_80700C28(M2C_FIELD((var_s0 + 0x80700000), u16 *, 0x714));
        temp_a0 = M2C_FIELD((var_s0 + 0x80700000), u16 *, 0x716);
        var_s0 += 4;
        func_80700C28(temp_a0);
    } while (var_s0 < 8);
}
