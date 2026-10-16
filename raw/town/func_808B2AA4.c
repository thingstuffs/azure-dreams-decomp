#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700D6C(s16);                         /* extern */

void func_807002A4(s32 arg0) {
    func_80700D6C(M2C_FIELD(((arg0 * 2) + 0xA0700000), s16 *, 0xF2C));
}
