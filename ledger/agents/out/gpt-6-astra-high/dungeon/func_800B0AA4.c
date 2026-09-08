#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A48F0();            /* extern */

/* Process the target with parameters 7 and 0x10 and report success. */
s32 func_800B6204(M2C_UNK target) {
    func_800A48F0(target, 7, 0x10);
    return 1;
}
