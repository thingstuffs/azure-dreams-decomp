#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80033C84();                   /* extern */
extern M2C_UNK D_800816C0;

void func_80033C8C(void) {
    void *var_s1;
    s32 var_s0;

    var_s1 = &D_800816C0;
    var_s0 = 0;
    do {
        func_80033C84(var_s1);
        var_s0 += 1;
        var_s1 = (void *)((u8 *)var_s1 + 0x64);
    } while (var_s0 < 0x14);
}
