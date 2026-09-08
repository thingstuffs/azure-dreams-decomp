#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Invoke operation 0xb for the target with both options cleared. */
void func_8001C25C(M2C_UNK target) {
    func_80402F84(target, 0xb, 0, 0);
}
