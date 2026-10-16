#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388(void *);                      /* extern */
s16 func_800C2AE8(void *);                          /* extern */
M2C_UNK func_800C4174(s32, void *, M2C_UNK);        /* extern */

void func_800CE6E4(s32 arg0, void *arg1, M2C_UNK arg2) {
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if (func_800C2AE8(arg1) < M2C_FIELD(arg1, s16 *, 0xA)) {
        M2C_FIELD(arg1, s16 *, 0xA) = func_800C2AE8(arg1);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        func_800C4174(arg0, arg1, arg2);
        return;
    }
    func_80095388(arg1);
}
