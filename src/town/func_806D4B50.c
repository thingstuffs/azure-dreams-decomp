#include "common.h"
#include "m2c_compat.h"

s32 func_800176B8(s32, s32, s32, s32);                                /* extern */
s32 initialize_state_two_entries_pointer();                     /* extern */
M2C_UNK func_800188E8();   /* extern */

/* Run the follow-up handlers when func_800176B8 returns a nonzero result. */
s32 run_followup_handlers_after_dispatch(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    s32 handler_result;

    handler_result = func_800176B8(input_a, input_b, input_c, input_d);
    if (handler_result != 0) {
        initialize_state_two_entries_pointer(0x146E);
        func_800188E8(0x990, 3, 2);
    }
    return handler_result;
}
