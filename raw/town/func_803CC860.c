#include "common.h"
#include "m2c_compat.h"

s32 func_8001D450(M2C_UNK);                         /* extern */
M2C_UNK func_8001D7CC(s16, s16, s16);               /* extern */

void func_8001D860(s32 arg0, void *arg1, M2C_UNK arg2) {
    void *temp_v0;

    temp_v0 = (M2C_FIELD(((func_8001D450(arg2) * 8) + arg0), s16 *, 2) * 8) + M2C_FIELD(arg1, s32 *, 0x14);
    func_8001D7CC(M2C_FIELD(temp_v0, s16 *, 0), M2C_FIELD(temp_v0, s16 *, 2), M2C_FIELD(temp_v0, s16 *, 4));
}
