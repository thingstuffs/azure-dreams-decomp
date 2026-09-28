#include "common.h"
#include "shared/sound_volume.h"


/* Returns volume scale [0] / [1] / [2] for selector 2 / 1 / 4, zero for any other selector. */
s32 func_80053E90(s32 selector) {
    s32 scale;
    if (selector == 2) {
        goto L_case2;
    }
    if (selector >= 3) {
        goto L_ge3;
    }
    if (selector == 1) {
        goto L_case1;
    }
    scale = 0;
    goto L_end;
L_ge3:
    if (selector != 4) {
        scale = 0;
        goto L_end;
    }
    scale = volumeScale[2];
    goto L_end;
L_case1:
    scale = volumeScale[1];
    goto L_end;
L_case2:
    scale = volumeScale[0];
L_end:
    return scale;
}
