#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 set_or_clear_actor_status_slot(State *, s32, s8);
extern s32 generate_random_value(void);
extern s32 check_entity_flag_20000000(State *);

s32 roll_threshold_effect_variant_a(State *state_ptr, s16 limit_input, s8 byte_input) {
    State *state = state_ptr;
    s16 limit = limit_input;
    s8 byte_value = byte_input;
    s32 result;
    s32 dividend;
    s32 dispatch_v1;

    if (check_entity_flag_20000000(state) != 0) {
        result = 0;
        return result;
    }
    dividend = generate_random_value() & 0xFFFF;
    if (state->divisor != 0) {
        dispatch_v1 = dividend % state->divisor;
    } else {
        dispatch_v1 = 0;
    }
    {
        s32 signed_limit;

        result = (s32)limit << 16;
        signed_limit = result >> 16;
        result = dispatch_v1 < signed_limit;
        if (result != 0 || signed_limit == (result = 0xFF)) {
            dispatch_v1 =
                (s32)((u32)set_or_clear_actor_status_slot(state, 5, byte_value) << 16);
            result = 1;
            if (dispatch_v1 < 0) {
                result = 0;
                return result;
            }
        } else {
            result = 0;
        }
    }
    return result;
}
