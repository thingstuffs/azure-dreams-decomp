#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC(s32, s32, s32, s32);                                /* extern */
s32 func_80099194();                        /* extern */
M2C_UNK func_80099290();                         /* extern */
M2C_UNK func_800A5720();                         /* extern */

/* Computes a value, applies its context-dependent result, and finalizes the value. */
void func_800997FC(s32 context, s32 first_input, s32 second_input, s32 third_input) {
    s32 computed_value;

    computed_value = func_800990FC(context, first_input, second_input, third_input);
    func_80099290(func_80099194(context, computed_value));
    func_800A5720(computed_value);
}
