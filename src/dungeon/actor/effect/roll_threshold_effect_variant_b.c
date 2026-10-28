#include "shared/actor_status_ids.h"
#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 set_or_clear_actor_status_slot(State *, s32, s8);
extern s32 generate_random_value(void);
extern s32 initialize_object_configuration_x(State *);


/* Rolls against the actor's divisor and limit to set status slot 3, returning 1 on success. */
s32 roll_threshold_effect_variant_b(State *state_ptr, s16 limit_input, s16 byte_input) {
    State *state = state_ptr;
    s16 limit = limit_input;
    s8 byte_value = byte_input;
    s32 dividend;
    s32 roll;

    if (initialize_object_configuration_x(state) != 0) {
        return 0;
    }
    dividend = generate_random_value() & 0xFFFF;
    if (state->divisor != 0) {
        roll = dividend % state->divisor;
    } else {
        roll = 0;
    }
    if (roll < limit || limit == 0xFF) {
        roll = (s16)set_or_clear_actor_status_slot(state, STATUS_BLIND, byte_value);
        if (roll >= 0) {
            return 1;
        }
    }
    return 0;
}
