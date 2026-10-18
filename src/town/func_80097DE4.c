#include "common.h"

typedef struct TownMotionState {
    u8 pad_00[0xC];
    s32 x;
    s32 y;
    s32 z;
} TownMotionState;

extern u8 D_800CFCEE[9];
extern void clear_slot_n_3_copies_slot_n_0(TownMotionState *state);
extern void clear_the_global_state_s_fifth_word_copy_source_s_second(TownMotionState *state);
extern void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(TownMotionState *state);

/* Clear motion along blocked directions and update the affected axes. */
void clear_motion_along_blocked_directions_update_affected_axes(TownMotionState *state)
{
    if (D_800CFCEE[2] != 0 && state->x < 0) {
        state->x = 0;
        clear_slot_n_3_copies_slot_n_0(state);
    }

    if (D_800CFCEE[3] != 0 && state->x > 0) {
        state->x = 0;
        clear_slot_n_3_copies_slot_n_0(state);
    }

    if (D_800CFCEE[4] != 0 && state->y < 0) {
        state->y = 0;
        clear_the_global_state_s_fifth_word_copy_source_s_second(state);
    }

    if (D_800CFCEE[5] != 0 && state->y > 0) {
        state->y = 0;
        clear_the_global_state_s_fifth_word_copy_source_s_second(state);
    }

    if (D_800CFCEE[1] != 0 && state->z > 0) {
        state->z = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(state);
    }

    if (D_800CFCEE[0] != 0 && state->z < 0) {
        state->z = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(state);
    }
}
