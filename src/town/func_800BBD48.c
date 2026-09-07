#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_800718B0[];
extern u8 D_80082E78;
extern M2C_UNK D_800D1D1C;
extern M2C_UNK D_800D1D24;
extern M2C_UNK D_800D1D2C;

void func_800B94A8(void) {
    M2C_UNK **base;
    s32 var_a1;

    base = D_800718B0;
    base[0] = &D_800D1D1C;
    var_a1 = 1;
    if (D_80082E78 != 0x17) {
        var_a1 = 3;
        base[1] = &D_800D1D24;
        base[2] = &D_800D1D2C;
    }
    base[var_a1] = NULL;
}
