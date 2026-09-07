#include "common.h"
#include "m2c_compat.h"

s32 func_8008F3CC();                           /* extern */
s32 func_8008F41C();                           /* extern */
M2C_UNK func_8008F50C();             /* extern */
M2C_UNK func_8008F520();             /* extern */

void func_8008F2D4(s32 arg0, s32 *arg1) {
    s32 temp_a2;
    s32 temp_a2_2;

    temp_a2 = func_8008F3CC(arg1) << 0x10;
    if (*arg1 >= temp_a2) {
        func_8008F50C(arg0, arg1, temp_a2);
    }
    temp_a2_2 = (func_8008F41C(arg1) << 0x10) - 1;
    if (temp_a2_2 >= *arg1) {
        func_8008F520(arg0, arg1, temp_a2_2);
    }
}
