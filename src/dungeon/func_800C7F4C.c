#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C8900();            /* extern */
extern u8 D_800E3D40;

void func_800CD6AC(M2C_UNK arg0) {
    M2C_UNK var_a1;

    var_a1 = 0x40;
    if (D_800E3D40 != 0) {
        var_a1 = 0x400;
    }
    func_800C8900(arg0, var_a1, 0x10);
}
