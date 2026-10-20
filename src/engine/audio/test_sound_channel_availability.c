#include "shared/sound_state.h"
#include "common.h"



/* Returns whether the indexed availability bit is set and its lock bit is clear. */
s32 test_sound_channel_availability(s16 bit_index) {
    SoundPlaybackState *flags = &sound_playback_state;
    if (!(flags->flags04 & (0x1000000 << bit_index))) {
        if (sound_playback_state.flags00 & (0x10000 << bit_index))
            return 1;
    }
    return 0;
}
