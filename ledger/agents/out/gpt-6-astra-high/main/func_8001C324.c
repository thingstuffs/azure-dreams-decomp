#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Dispatches operation 0xf in mode 2 with the supplied target and value. */
void func_8001C324(M2C_UNK target, M2C_UNK value) {
    func_80402F84(target, 0xf, 2, value);
}
