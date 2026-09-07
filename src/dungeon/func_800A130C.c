#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A90E8();                        /* extern */

void func_800A6A6C(void) {
    s8 sp10[2];

    sp10[0] = 1;
    sp10[1] = 0x12;
    func_800A90E8((s8 *)&sp10[0]);
}
