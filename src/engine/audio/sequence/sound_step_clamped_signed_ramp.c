#include "common.h"
#include "engine/audio/sequence.h"



#define S16_FIELD(ptr, offset) (*(s16 *)((u8 *)(ptr) + (offset)))

/* The caller passes an audio_channel_controls entry; start_channel_note
 * declares the same channel words at +0x50 and +0x58. */
typedef struct SoundChannelRamp {
    u8 pad_00[0x50];
    s16 enabled;
    u16 value;
    s16 step;
    u16 limit;
    s32 direction;
} SoundChannelRamp;

/* Steps an enabled value toward its positive or negative limit. */
void sound_step_clamped_signed_ramp(void *state) {
    SoundChannelRamp *ramp = state;
    s32 next_value;
    s32 lower_limit;
    u16 upper_limit;

    if (ramp->enabled != 0) {
        if (ramp->direction != 0) {
            upper_limit = ramp->limit;
            if (((s16)ramp->value + ramp->step) < (s32) upper_limit) {
                ramp->value = ramp->value + (u16)ramp->step;
                return;
            }
            ramp->value = upper_limit;
            return;
        }
        next_value = (s16)ramp->value - ramp->step;
        lower_limit = -ramp->limit;
        if (lower_limit < next_value) {
            ramp->value = ramp->value - (u16)ramp->step;
            return;
        }
        S16_FIELD(state, 0x52) = lower_limit;
    }
}
