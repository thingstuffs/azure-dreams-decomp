#include "common.h"
#include "m2c_compat.h"

s32 func_8008F46C();                           /* extern */
s32 func_8008F4BC();                           /* extern */
void func_8008F534();             /* extern */
void func_8008F548();             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void func_8008F350(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = func_8008F46C(value) << 0x10;
    if (value[1] >= upper_bound) {
        func_8008F534(context, value, upper_bound);
    }
    lower_bound = (func_8008F4BC(value) << 0x10) - 1;
    if (lower_bound >= value[1]) {
        func_8008F548(context, value, lower_bound);
    }
}
