#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0E04;

void func_800A7554(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8003DB94(arg2, &D_800D0E04, 0);
    func_8009B218(arg0, arg1, arg2, 0);
}
