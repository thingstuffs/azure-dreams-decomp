#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800188D4();                            /* extern */
s32 func_8001ADE0();                             /* extern */
extern s16 D_8001B8AA;

s32 func_80017FFC(void) {
    if (func_8001ADE0(D_8001B8AA) == 0) {
        func_800188D4();
    }
    return 1;
}
