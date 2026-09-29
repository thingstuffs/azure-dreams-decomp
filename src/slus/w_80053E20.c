#include "common.h"
#include "shared/sound_volume.h"


extern void func_80054D64(void);
extern void func_800552C8(void);

/* Sets volume scale [0] / [1] / [2] for selector 2 / 1 / 4; [1] and [2] are re-applied at once. */
void func_80053E20(s16 value, s32 stat_index) {
    if (stat_index == 2) {
        goto L_case2;
    }
    if (stat_index >= 3) {
        goto L_ge3;
    }
    if (stat_index == 1) {
        goto L_case1;
    }
    return;
L_ge3:
    if (stat_index != 4) {
        return;
    }
    volumeScale[2] = value;
    func_80054D64();
    return;
L_case1:
    volumeScale[1] = value;
    func_800552C8();
    return;
L_case2:
    volumeScale[0] = value;
    return;
}
