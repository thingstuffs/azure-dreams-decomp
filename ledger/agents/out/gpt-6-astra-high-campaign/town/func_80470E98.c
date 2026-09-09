#include "common.h"

s32 func_8001A220(s32, s32, s32);                                /* extern */

/* Return whether func_8001A220 produces a value below -47. */
s32 func_80017E98(s32 first_input, s32 second_input, s32 third_input) {
    return func_8001A220(first_input, second_input, third_input) < -0x2F;
}
