#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Pass the target to func_80402F84 with code 0x13 and zero options. */
void func_8001C3C4(M2C_UNK target) {
    func_80402F84(target, 0x13, 0, 0);
}
