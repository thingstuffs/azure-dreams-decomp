#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016CD8(s32);                         /* extern */
M2C_UNK func_80016D80(s32, M2C_UNK);                /* extern */
s32 func_80017990(M2C_UNK);                         /* extern */

void func_80016550(s32 arg0, M2C_UNK arg1) {
    if (func_80017990(7) != 0) {
        func_80016CD8(arg0);
    }
    func_80016D80(arg0, arg1);
}
