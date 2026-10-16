#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards value to initCardMessageObject with fixed options (1, 0, 0). */
void func_8001C0F4(M2C_UNK value) {
    initCardMessageObject(value, 1, 0, 0);
}
