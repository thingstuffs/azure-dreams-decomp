#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 func_80037534();                                /* extern */
M2C_UNK func_800478B8();                     /* extern */

/* Forwards the value to func_800478B8 when func_80037534 returns zero. */
void func_80036C44(M2C_UNK unused_0, M2C_UNK unused_1, M2C_UNK value) {
    if (func_80037534() == 0) {
        func_800478B8(value);
    }
}
