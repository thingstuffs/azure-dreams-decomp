#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */

void func_800C71F8(void *arg2) {
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_800C4174();
    }
}
