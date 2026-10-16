#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards value to initCardMessageObject with fixed arguments 10, 0, and 0. */
void func_8001C234(M2C_UNK value) {
    initCardMessageObject(value, 0xa, 0, 0);
}
