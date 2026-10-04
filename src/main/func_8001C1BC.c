#include "common.h"
#include "m2c_compat.h"

u8 *func_80402F84();   /* extern */

/* Dispatch operation 6 in mode 2 with the supplied target and value. */
void func_8001C1BC(M2C_UNK target, M2C_UNK value) {
    func_80402F84(target, 6, 2, value);
}
