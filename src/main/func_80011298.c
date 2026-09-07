#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80023E14();                         /* extern */
M2C_UNK func_800240EC();                         /* extern */
M2C_UNK func_80024160();                         /* extern */

void func_80024298(s32 arg0) {
    s32 temp_s0;

    if (arg0 != 0) {
        temp_s0 = arg0 + 0x20;
        func_800240EC(temp_s0);
        func_80024160(temp_s0);
        func_80023E14(temp_s0);
    }
}
