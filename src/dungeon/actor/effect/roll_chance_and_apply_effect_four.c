#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 set_or_clear_actor_status_slot(State *, s32, s8);
extern s32 generate_random_value(void);
extern s32 is_linked_entity_flagged_10000000(State *);

/* Roll the state's chance and, on a hit, apply effect 4 to it. */
s32 roll_chance_and_apply_effect_four(State *state, s16 value, s8 flag) {
    s32 roll;
    u16 chance;

    if (is_linked_entity_flagged_10000000(state) != 0) {
        return 0;
    }
    roll = generate_random_value() & 0xFFFF;
    if (state->divisor != 0) {
        chance = roll % state->divisor;
    } else {
        chance = 0;
    }
    if (chance < value || value == 255) {
        if ((s32)((u32)set_or_clear_actor_status_slot(state, 4, flag) << 16) >= 0) {
            return 1;
        }
    }
    return 0;
}
