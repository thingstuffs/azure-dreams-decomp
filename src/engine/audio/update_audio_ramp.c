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

    switch (ramp->unk_0C) {
    case 1:
        next_value = ramp->unk_10 + ramp->unk_14;
        ramp->unk_10 = next_value;
        if (next_value >= 0x80) {
            ramp->unk_10 = 0x7F;
            ramp->unk_0C = 3;
        }
        break;
    case 2:
        next_value = ramp->unk_10 - ramp->unk_14;
        target = ramp->unk_12;
        ramp->unk_10 = next_value;
        if (next_value < ramp->unk_12) {
            ramp->unk_10 = target;
            ramp->unk_0C = 3;
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
