#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

s32 func_800176B8(s32, s32, s32, s32);                                /* extern */
void initialize_state_two_entries_pointer(s32 bit_index);                     /* extern */
void func_800188E8(s32, s32, s32);   /* extern */

/* Run the follow-up handlers when func_800176B8 returns a nonzero result. */
s32 run_followup_handlers_after_dispatch(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    s32 handler_result;

    handler_result = func_800176B8(input_a, input_b, input_c, input_d);
    if (handler_result != 0) {
        initialize_state_two_entries_pointer(Ft_niko_love);
        func_800188E8(F_sbs34_pad16, 3, 2);
    }
    return handler_result;
}
