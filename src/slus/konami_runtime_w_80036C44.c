#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 func_80037534();                                /* extern */
M2C_UNK func_800478B8();                     /* extern */

void func_80036C44(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_80037534() == 0) {
        func_800478B8(arg2);
    }
}
