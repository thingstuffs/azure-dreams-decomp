#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */

void func_8016E254(u16 *arg0, void *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = *arg0 + 1;
    *arg0 = temp_v0;
    if ((s16) temp_v0 < 9) {
        temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x100;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_2;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
    }
    func_800478B8(arg2);
}
