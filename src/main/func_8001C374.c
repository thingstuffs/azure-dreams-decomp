#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards the target to initCardMessageObject with fixed arguments 0x11, 0, and 0. */
void func_8001C374(M2C_UNK target) {
    initCardMessageObject(target, 0x11, 0, 0);
}
