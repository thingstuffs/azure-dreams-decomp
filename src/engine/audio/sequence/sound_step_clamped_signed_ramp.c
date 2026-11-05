#include "common.h"
#include "engine/audio/sequence.h"



/* Steps an enabled value toward its positive or negative limit. */
void sound_step_clamped_signed_ramp(AudioChannelControl *state) {
    s32 next_value;
    s32 lower_limit;
    u16 upper_limit;

    if (state->f50 != 0) {
        if (state->f58 != 0) {
            upper_limit = state->f56;
            if (((s16)state->f52 + state->f54) < (s32) upper_limit) {
                state->f52 = state->f52 + (u16)state->f54;
                return;
            }
            state->f52 = upper_limit;
            return;
        }
        next_value = (s16)state->f52 - state->f54;
        lower_limit = -state->f56;
        if (lower_limit < next_value) {
            state->f52 = state->f52 - (u16)state->f54;
            return;
        }
        state->f52 = lower_limit;
    }
}
