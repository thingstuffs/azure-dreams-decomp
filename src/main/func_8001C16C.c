#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards a target and value to initCardMessageObject with fixed parameters 4 and 2. */
void func_8001C16C(M2C_UNK target, M2C_UNK value) {
    initCardMessageObject(target, 4, 2, value);
}
