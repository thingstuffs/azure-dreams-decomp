#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018C74(M2C_UNK);                     /* extern */
M2C_UNK func_80018CEC(M2C_UNK);                     /* extern */
s32 func_80018D6C(M2C_UNK);                         /* extern */

s32 func_80016C20(void) {
    if (func_80018D6C(0xFB1) == 0) {
        func_80018CEC(0xFCB);
        func_80018CEC(0xFCD);
        return 0;
    }
    func_80018C74(0xFD3);
    return 1;
}
