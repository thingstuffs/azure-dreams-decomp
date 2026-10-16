#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forward the target and value to initCardMessageObject with selectors 0 and 1. */
void func_8001C0CC(M2C_UNK target, M2C_UNK value) {
    initCardMessageObject(target, 0, 1, value);
}
