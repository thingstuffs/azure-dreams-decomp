#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 set_or_clear_actor_status_slot(State *, s32, s8);
extern s32 generate_random_value(void);
extern s32 initialize_object_configuration_x(State *);


/* Rolls against the actor's divisor and limit to set status slot 3, returning 1 on success. */
s32 roll_threshold_effect_variant_b(State *state_ptr, s16 limit_input, s8 byte_input) {
    State *state = state_ptr;
    s16 limit = limit_input;
    s8 byte_value = byte_input;
    s32 result;
    s32 dividend;
    s32 dispatch_v1;

    if (initialize_object_configuration_x(state) != 0) {
        result = 0;
        return result;
    }
    dividend = generate_random_value() & 0xFFFF;
    if (state->divisor != 0) {
        dispatch_v1 = dividend % state->divisor;
    } else {
        dispatch_v1 = 0;
    }
    do {
        {
            s32 signed_limit;

            result = (s32)limit << 16;
            signed_limit = result >> 16;
            result = dispatch_v1 < signed_limit;
            if (result == 0) {
                result = 0xFF;
                if (signed_limit != result) {
                    break;
                }
            }
            dispatch_v1 =
                (s32)((u32)set_or_clear_actor_status_slot(state, 3, byte_value) << 16);
            result = 1;
            if (dispatch_v1 >= 0) {
                goto done;
            }
        }

    } while (0);
    result = 0;
done:
    return result;
}
