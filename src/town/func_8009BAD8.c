#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();              /* extern */
M2C_UNK func_8009A1E8();       /* extern */
extern M2C_UNK D_800D0130;

void func_80099238(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80094984(&D_800D0130, arg0, arg2);
    func_8009A1E8(arg0, arg1, arg2);
}
