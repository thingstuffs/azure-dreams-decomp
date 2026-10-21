#include "common.h"
#include "shared/sound_volume.h"

#include "common.h"
#include "engine/audio.h"

/* Sets volume scale [1] and re-applies it through func_800552C8. */
void sound_set_sequence_volume_scale(s16 new_value) {
    g_volume_scale[1] = new_value;
    apply_scaled_sound_slot_volume();
}
