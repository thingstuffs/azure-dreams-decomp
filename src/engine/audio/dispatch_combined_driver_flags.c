#include "common.h"
#include "engine/audio.h"
#include "slus.h"

extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[24];

/* Combines the active audio voice masks and passes them to SpuSetKey with selector 0. */
void dispatch_combined_driver_flags(void) {
    s32 flags;
    s32 flag_index;

    flags = 0;
    for (flag_index = 0; flag_index < audio_voice_count[0]; flag_index++) {
        flags |= audio_voice_masks[flag_index];
    }
    SpuSetKey(0, flags);
}
