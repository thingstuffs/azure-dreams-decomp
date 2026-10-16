#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Pass the target to initCardMessageObject with code 0x13 and zero options. */
void func_8001C3C4(M2C_UNK target) {
    initCardMessageObject(target, 0x13, 0, 0);
}
