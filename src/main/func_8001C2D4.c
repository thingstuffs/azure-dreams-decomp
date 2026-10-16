#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards value to initCardMessageObject with fixed arguments 3, 0, and 0. */
void func_8001C2D4(M2C_UNK value) {
    initCardMessageObject(value, 3, 0, 0);
}
