#include "common.h"
#include "slus/audio_voice_data.h"
#include "engine/audio.h"
#include "slus.h"
/* Combines the active audio voice masks and passes them to SpuSetKey with selector 0. */
void dispatch_combined_driver_flags(s32 unused) {
    s32 flags;
    s32 flag_index;

    flags = 0;
    for (flag_index = 0; flag_index < audio_voice_count[0]; flag_index++) {
        flags |= audio_voice_masks[flag_index];
    }
    SpuSetKey(0, flags);
}
