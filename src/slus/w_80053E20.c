#include "common.h"
#include "shared/sound_volume.h"

extern void func_80054D64(void);
extern void func_800552C8(void);

/* Sets volume scale [0] / [1] / [2] for selector 2 / 1 / 4; [1] and [2] are re-applied at once. */
void func_80053E20(s16 value, s32 stat_index) {
    switch (stat_index) {
    case 4:
        volumeScale[2] = value;
        func_80054D64();
        break;
    case 1:
        volumeScale[1] = value;
        func_800552C8();
        break;
    case 2:
        volumeScale[0] = value;
        break;
    }
}
