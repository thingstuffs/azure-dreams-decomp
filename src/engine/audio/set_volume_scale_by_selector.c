#include "common.h"
#include "shared/sound_volume.h"


/* Sets volume scale [0] / [1] / [2] for selector 2 / 1 / 4; [1] and [2] are re-applied at once. */
void set_volume_scale_by_selector(s16 value, s32 stat_index) {
    switch (stat_index) {
    case 4:
        g_volume_scale[2] = value;
        apply_scaled_cd_stream_volume();
        break;
    case 1:
        g_volume_scale[1] = value;
        apply_scaled_sound_slot_volume();
        break;
    case 2:
        g_volume_scale[0] = value;
        break;
    }
}
