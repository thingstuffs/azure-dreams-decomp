#include "common.h"
#include "m2c_compat.h"

s32 func_80016440(M2C_UNK);                         /* extern */
M2C_UNK func_800167BC(s16, s16, s16);               /* extern */

void func_80016850(s32 arg0, void *arg1, M2C_UNK arg2) {
    void *temp_v0;

    temp_v0 = (M2C_FIELD(((func_80016440(arg2) * 8) + arg0), s16 *, 2) * 8) + M2C_FIELD(arg1, s32 *, 0x14);
    func_800167BC(M2C_FIELD(temp_v0, s16 *, 0), M2C_FIELD(temp_v0, s16 *, 2), M2C_FIELD(temp_v0, s16 *, 4));
}
