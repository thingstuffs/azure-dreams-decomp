#include "common.h"

extern s32 D_80019AFC;
extern s32 select_state_result_with_lookup_overrides(void);
extern s32 select_data_by_kind_and_index(s32, s32, s32);

/* Dispatch the inputs according to the current state. */
s32 dispatch_inputs_by_current_state(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    s32 state = D_80019AFC;

    if (state == 0) {
        return select_state_result_with_lookup_overrides();
    }
    if (state == 2) {
        return select_data_by_kind_and_index(input_a, input_b, input_c);
    }
    return 0;
}
