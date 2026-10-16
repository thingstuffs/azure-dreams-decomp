#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80701808(s16);                         /* extern */

void func_80700D54(s32 arg0) {
    func_80701808(M2C_FIELD(((arg0 * 2) + 0x80700000), s16 *, 0xBB4));
}
