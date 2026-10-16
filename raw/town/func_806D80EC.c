#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800178D0(s32);                         /* extern */
M2C_UNK func_80017978(s32, M2C_UNK);                /* extern */
s32 func_80018640(M2C_UNK);                         /* extern */

void func_800168EC(s32 arg0, M2C_UNK arg1) {
    if (func_80018640(0x3EC) != 0) {
        func_800178D0(arg0);
    }
    func_80017978(arg0, arg1);
}
