#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"

/* Raises or lowers the active gauge, calling its callback after an update or returning -1 on depletion. */
s32 update_audio_fade(SoundTask *gauge)
{
    u16 next_value;

    switch (gauge->fade_mode) {
    case 1:
        next_value = (u16)(gauge->fade_level + (u16)gauge->fade_in_step);
        gauge->fade_level = next_value;
        if (gauge->fade_target < (s16)next_value) {
            gauge->fade_level = (s16)gauge->fade_target;
            gauge->fade_mode = 3;
        }
        break;
    case 2:
        next_value = (u16)(gauge->fade_level - (u16)gauge->fade_out_step);
        gauge->fade_level = next_value;
        if ((s16)next_value <= 0) {
            gauge->fade_level = 0;
            return -1;
        }
        break;
    default:
        return 0;
    }

    if (gauge->callback != 0) {
        gauge->callback();
    }
    return 0;
}
