#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004E99C();

void func_800B15B8(void *arg0) {
    register void *var_s0 ASM_REG("$16");
    register s32 var_s1 ASM_REG("$17");

    var_s1 = 0;
    var_s0 = M2C_FIELD(arg0, void **, 0xCC);
    do {
        *M2C_FIELD(var_s0, s32 **, 0x10) = 0;
        var_s1 += 1;
        func_8004E99C(*M2C_FIELD(var_s0, s32 **, 0x38));
        *M2C_FIELD(var_s0, s32 **, 0x38) = 0;
        func_8004E99C(*M2C_FIELD(var_s0, s32 **, 0x4C));
        *M2C_FIELD(var_s0, s32 **, 0x4C) = 0;
        func_8004E99C(*M2C_FIELD(var_s0, s32 **, 0x60));
        *M2C_FIELD(var_s0, s32 **, 0x60) = 0;
        var_s0 += 4;
    } while (var_s1 < 5);
}
