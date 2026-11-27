#include "shared/sound_state.h"
#include "shared/sound_volume.h"
#include "common.h"
#include "engine/audio.h"

#ifndef NULL
#define NULL 0
#endif

/* Sibling struct (matches src/code.c's SoundTask and src/w_800544A4.c's
 * SoundTask field-for-field): no-arg completion callback at 0x0, s32
 * counter at 0x4, s16 pair at 0x8/0xA, state at 0xC, then the s16 fields
 * this function ramps (0x10 current value, 0x12 clamp target, 0x14 step). */

/* Advances the active ramp, clamps its value at the limit, and invokes its callback. */
void update_audio_ramp(SoundTask *ramp) {
    s16 next_value;
    s16 target;
    sound_task_callback_fn callback;

    switch (ramp->ramp_mode) {
    case 1:
        next_value = ramp->ramp_level + ramp->ramp_step;
        ramp->ramp_level = next_value;
        if (next_value >= 0x80) {
            ramp->ramp_level = 0x7F;
            ramp->ramp_mode = 3;
        }
        break;
    case 2:
        next_value = ramp->ramp_level - ramp->ramp_step;
        target = ramp->ramp_target;
        ramp->ramp_level = next_value;
        if (next_value < ramp->ramp_target) {
            ramp->ramp_level = target;
            ramp->ramp_mode = 3;
        }
        break;
    default:
        return;
    }

    callback = ramp->callback;
    if (callback != NULL) {
        callback();
    }
}
