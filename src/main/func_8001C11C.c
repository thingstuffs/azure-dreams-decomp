#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards the target and value to initCardMessageObject with both selectors set to 2. */
void func_8001C11C(M2C_UNK target, M2C_UNK value) {
    initCardMessageObject(target, 2, 2, value);
}
