#include "common.h"

s16 func_8004CAA0(s32, s32, s32);                                /* extern */

/* Forward three values to func_8004CAA0 and return its result. */
s16 func_80027DD0(s32 first_value, s32 second_value, s32 third_value) {
    return func_8004CAA0(first_value, second_value, third_value);
}
