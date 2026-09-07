#include "common.h"

/* manual g1 strike 2: preserve the incoming second argument through the call */
#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_8003F6D4();
extern M2C_UNK D_800814F8;

M2C_UNK *func_800437A4(s16 arg0, M2C_UNK arg1) {
    s32 var_a3;

    if (arg0 == 0x38) {
        var_a3 = 0x426D;
    } else if (arg0 >= 0x3A) {
        var_a3 = ((arg0 - 0x3A) * 0x2B) + 0x1BA7;
    } else {
        var_a3 = ((arg0 - 1) * 0x2B) + 0x56F0;
    }
    func_8003F6D4(0x11, arg1, &D_800814F8, var_a3);
    return &D_800814F8;
}
