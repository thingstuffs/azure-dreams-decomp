#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards value to initCardMessageObject with fixed arguments 7, 0, 0. */
void func_8001C2FC(M2C_UNK value) {
    initCardMessageObject(value, 7, 0, 0);
}
