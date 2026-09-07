#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_80047C00();                            /* extern */
s32 func_80047CD8();                             /* extern */
M2C_UNK func_80047EEC();                    /* extern */
M2C_UNK func_800481E0();                            /* extern */

void func_80047F90(s16 arg0) {
    s32 temp_v0;

    func_800481E0();
    func_80047C00();
    temp_v0 = func_80047CD8(arg0);
    if (temp_v0 != 0) {
        func_8003F320();
        func_80047EEC(arg0, temp_v0);
    }
}
