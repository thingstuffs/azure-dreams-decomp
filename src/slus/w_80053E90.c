#include "common.h"
#include "shared/sound_volume.h"


/* Returns volume scale [0] / [1] / [2] for selector 2 / 1 / 4, zero for any other selector. */
s32 func_80053E90(s32 selector) {
    switch (selector) {
    case 4:
        return volumeScale[2];
    case 1:
        return volumeScale[1];
    case 2:
        return volumeScale[0];
    default:
        return 0;
    }
}
