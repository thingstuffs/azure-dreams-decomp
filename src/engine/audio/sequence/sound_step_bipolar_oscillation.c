#include "common.h"
#include "engine/audio/sequence.h"


/* manual g1 strike 2: order the negative-direction compare like retail */

/* Step the enabled oscillation between its limits, or reset its value to zero. */
void sound_step_bipolar_oscillation(AudioChannelControl *state) {
    s32 next_value;
    s32 lower_limit;

    if (state->vibrato_rate != 0) {
        if (state->vibrato_rising != 0) {
            if ((state->vibrato_offset + state->vibrato_step) < state->vibrato_limit) {
                state->vibrato_offset = (u16)state->vibrato_offset + (u16)state->vibrato_step;
                return;
            }
            state->vibrato_rising = 0;
            state->vibrato_offset = (u16)state->vibrato_limit;
            return;
        }

        next_value = state->vibrato_offset - state->vibrato_step;
        lower_limit = -state->vibrato_limit;
        if (lower_limit < next_value) {
            state->vibrato_offset = (u16)state->vibrato_offset - (u16)state->vibrato_step;
            return;
        }
        state->vibrato_rising = 1;
        state->vibrato_offset = -((s16)(u16)state->vibrato_limit);
        return;
    }
    state->vibrato_offset = 0;
}
