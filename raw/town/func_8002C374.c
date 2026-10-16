#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388(void *);                      /* extern */
M2C_UNK func_800C9D40(s32, void *, M2C_UNK);        /* extern */

void func_800C9AD4(s32 arg0, void *arg1, M2C_UNK arg2) {
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    func_80095388(arg1);
    if (M2C_FIELD(arg1, s32 *, 0x14) >= 0) {
        func_800C9D40(arg0, arg1, arg2);
    }
}
