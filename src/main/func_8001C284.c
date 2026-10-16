#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Forwards the input to initCardMessageObject with arguments 0xC, 0, and 0. */
void func_8001C284(M2C_UNK input) {
    initCardMessageObject(input, 0xc, 0, 0);
}
