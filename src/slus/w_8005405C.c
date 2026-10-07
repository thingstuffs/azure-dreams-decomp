#include "shared/sound_state.h"
#include "common.h"



/* Returns whether the indexed availability bit is set and its lock bit is clear. */
s32 func_8005405C(s16 bit_index) {
    SoundPlaybackState *flags = &D_800847D0;
    if (!(flags->flags04 & (0x1000000 << bit_index))) {
        if (D_800847D0.flags00 & (0x10000 << bit_index))
            return 1;
    }
    return 0;
}
