#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(M2C_UNK);                         /* extern */
M2C_UNK func_80042B68(s32, M2C_UNK);                /* extern */

s32 func_8016A258(s32 arg0) {
    if ((func_80042900(0x19) << 0x10) == 0) {
        return 0;
    }
    func_80042B68(arg0, 0x19);
    return 1;
}
