#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_8009B218(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_800ED15C;

void func_800C620C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8003DB94(arg2, &D_800ED15C, 0);
    func_8009B218(arg0, arg1, arg2, 0);
}
