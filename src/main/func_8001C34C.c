#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Passes value to initCardMessageObject with fixed arguments 0x10, 0, 0. */
void func_8001C34C(M2C_UNK value) {
    initCardMessageObject(value, 0x10, 0, 0);
}
