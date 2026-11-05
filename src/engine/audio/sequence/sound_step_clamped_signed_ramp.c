#include "common.h"
#include "engine/audio/sequence.h"



/* Steps an enabled value toward its positive or negative limit. */
void sound_step_clamped_signed_ramp(AudioChannelControl *state) {
    s32 next_value;
    s32 lower_limit;
    u16 upper_limit;

    if (state->portamento_time != 0) {
        if (state->portamento_rising != 0) {
            upper_limit = state->portamento_span;
            if (((s16)state->portamento_offset + state->portamento_step) < (s32) upper_limit) {
                state->portamento_offset = state->portamento_offset + (u16)state->portamento_step;
                return;
            }
            state->portamento_offset = upper_limit;
            return;
        }
        next_value = (s16)state->portamento_offset - state->portamento_step;
        lower_limit = -state->portamento_span;
        if (lower_limit < next_value) {
            state->portamento_offset = state->portamento_offset - (u16)state->portamento_step;
            return;
        }
        state->portamento_offset = lower_limit;
    }
}
