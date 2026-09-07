#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025040();  /* extern */
s32 func_8004B404();                         /* extern */

void func_80026DE0(s32 arg0, M2C_UNK arg1) {
    s32 temp_v0;

    temp_v0 = func_8004B404(0x91);
    if (temp_v0 != 0) {
        func_80025040(temp_v0, arg0, arg1, 0x48);
    }
}
