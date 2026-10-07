#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"

/* Canonical status block shared across the D_800847D0 family (w_800540A8.c,
   w_80054C58.c, w_8005405C.c, w_800559B4.c). Only flags1 is touched here. */

/* Canonical "task/timer object" struct established in w_800559B4.c. field0 is a
   callback pointer (set to func_80054D64 there); field8/field10 are the two
   s16 fields this function reads. */


extern void func_8005A56C(s32 mode, s32 level_a, s32 level_b);

/* When status flag 0x400 is set: D_80084858's level, scaled by volume scale [2], goes to func_8005A56C (mode 0). */
void func_80054D64(void) {
    s16 level;
    s32 scaled;

    if (D_800847D0.flags00 & 0x400) {
        SoundTask *task = &D_80084858;

        level = (task->unk_08 * volumeScale[2]) / 32767;
        scaled = level * task->unk_10;
        level = scaled / 128;
        func_8005A56C(0, level, level);
    }
}
