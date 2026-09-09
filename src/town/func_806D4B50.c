#include "common.h"
#include "m2c_compat.h"

s32 func_800176B8(s32, s32, s32, s32);                                /* extern */
M2C_UNK func_80018594();                     /* extern */
M2C_UNK func_800188E8();   /* extern */

/* Run the follow-up handlers when func_800176B8 returns a nonzero result. */
s32 func_80016B50(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    s32 handler_result;

    handler_result = func_800176B8(input_a, input_b, input_c, input_d);
    if (handler_result != 0) {
        func_80018594(0x146E);
        func_800188E8(0x990, 3, 2);
    }
    return handler_result;
}
