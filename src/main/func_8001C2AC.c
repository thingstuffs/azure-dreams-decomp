#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Calls initCardMessageObject with the target and fixed arguments (13, 0, 0). */
void func_8001C2AC(M2C_UNK target) {
    initCardMessageObject(target, 0xd, 0, 0);
}
