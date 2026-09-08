#include "common.h"
#include "m2c_compat.h"

s32 func_8008F3CC();                           /* extern */
s32 func_8008F41C();                           /* extern */
M2C_UNK func_8008F50C();             /* extern */
M2C_UNK func_8008F520();             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void func_8008F2D4(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = func_8008F3CC(value) << 0x10;
    if (*value >= upper_bound) {
        func_8008F50C(context, value, upper_bound);
    }
    lower_bound = (func_8008F41C(value) << 0x10) - 1;
    if (lower_bound >= *value) {
        func_8008F520(context, value, lower_bound);
    }
}
