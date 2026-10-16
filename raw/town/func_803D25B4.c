#include "common.h"
#include "m2c_compat.h"

s32 func_800191A4(M2C_UNK);                         /* extern */
M2C_UNK func_80019520(s16, s16, s16);               /* extern */

void func_800195B4(s32 arg0, void *arg1, M2C_UNK arg2) {
    void *temp_v0;

    temp_v0 = (M2C_FIELD(((func_800191A4(arg2) * 8) + arg0), s16 *, 2) * 8) + M2C_FIELD(arg1, s32 *, 0x14);
    func_80019520(M2C_FIELD(temp_v0, s16 *, 0), M2C_FIELD(temp_v0, s16 *, 2), M2C_FIELD(temp_v0, s16 *, 4));
}
