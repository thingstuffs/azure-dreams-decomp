#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AE56C();                         /* extern */

/* Calls func_800AE56C with the offset increased by 0x20. */
void func_800AF234(s32 offset) {
    func_800AE56C(offset + 0x20);
}
