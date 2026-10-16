#include "common.h"
#include "m2c_compat.h"

s32 func_800192AC(M2C_UNK);                         /* extern */
M2C_UNK func_8001A64C(s16);                         /* extern */

void func_80019B68(s32 arg0, void *arg1, M2C_UNK arg2) {
    func_8001A64C(M2C_FIELD(((M2C_FIELD(((func_800192AC(arg2) * 8) + arg0), s16 *, 2) * 8) + M2C_FIELD(arg1, s32 *, 0x14)), s16 *, 4));
}
