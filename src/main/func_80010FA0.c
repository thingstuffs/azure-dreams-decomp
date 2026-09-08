#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80023A78();      /* extern */
M2C_UNK func_80023E14();                         /* extern */
M2C_UNK func_80023F94(s32, M2C_UNK, M2C_UNK);                            /* extern */

void func_80023FA0(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80023F94(arg0, arg1, arg2);
    func_80023A78(arg0 + 0x24C, arg0 + 0x224, arg0 + 0x234, arg2);
    func_80023E14(arg0);
}
