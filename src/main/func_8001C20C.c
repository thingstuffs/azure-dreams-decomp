#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Calls initCardMessageObject for the target with fixed arguments 9, 0, and 0. */
void func_8001C20C(M2C_UNK target) {
    initCardMessageObject(target, 9, 0, 0);
}
