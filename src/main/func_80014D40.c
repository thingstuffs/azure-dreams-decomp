#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80027AFC();                /* extern */
M2C_UNK func_80027C60();                            /* extern */
M2C_UNK func_800A68C0();                            /* extern */

void func_80027D40(s32 arg0) {
    func_800A68C0();
    func_80027C60();
    func_80027AFC(arg0, 2);
}
