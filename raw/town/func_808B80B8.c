#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80003BCC(M2C_UNK);                     /* extern */
M2C_UNK func_80003C1C(M2C_UNK);                     /* extern */
s32 func_80003C70(M2C_UNK);                         /* extern */

void func_800038B8(void) {
    if ((func_80003C70(0x20C) == 0) && (func_80003C70(0x268) == 0)) {
        func_80003BCC(0x24C);
        return;
    }
    func_80003C1C(0x24C);
}
