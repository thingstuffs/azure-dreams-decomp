#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Invoke operation 0xb for the target with both options cleared. */
void func_8001C25C(M2C_UNK target) {
    initCardMessageObject(target, 0xb, 0, 0);
}
