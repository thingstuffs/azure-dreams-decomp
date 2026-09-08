#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Calls func_80402F84 with the target and fixed arguments (13, 0, 0). */
void func_8001C2AC(M2C_UNK target) {
    func_80402F84(target, 0xd, 0, 0);
}
