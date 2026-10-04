#include "common.h"
#include "m2c_compat.h"

u8 *func_80402F84();   /* extern */

/* Dispatch operation 5 for the target with one value. */
void func_8001C194(M2C_UNK target, M2C_UNK value) {
    func_80402F84(target, 5, 1, value);
}
