#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003832C();                         /* extern */
s32 func_80053EF0();                         /* extern */

void func_800382F0(s32 arg0) {
    if (func_80053EF0(4) == 0) {
        func_8003832C(arg0);
    }
}
