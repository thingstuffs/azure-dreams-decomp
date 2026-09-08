#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047358();            /* extern */
extern M2C_UNK D_80408D28;

/* Forwards value to func_80047358 with D_80408D28 and constant 0x15. */
void func_8001E6CC(M2C_UNK value) {
    func_80047358(value, &D_80408D28, 0x15);
}
