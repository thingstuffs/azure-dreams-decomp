#include "common.h"
#include "shared/sound_volume.h"


/* Returns volume scale [0] / [1] / [2] for selector 2 / 1 / 4, zero for any other selector. */
s32 get_volume_scale_by_selector(s32 selector) {
    switch (selector) {
    case 4:
        return g_volume_scale[2];
    case 1:
        return g_volume_scale[1];
    case 2:
        return g_volume_scale[0];
    default:
        return 0;
    }
}
