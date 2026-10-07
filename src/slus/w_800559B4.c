#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"

/* Canonical "task/timer object" struct shared with func_80055990's own SoundTask
   (src/code.c) and w_800540A8.c's SoundTask / w_80054C58.c's SoundTask: field0 is
   revealed here as a function pointer (this function stores a callback address into it),
   and the two 4-byte pad windows are each a pair of s16 fields. */

/* Same layout as SoundTask (SoundTask family), independently named per its own
   global address per convention. */

/* Extends the SoundPlaybackState view already established in w_800540A8.c / w_80054C58.c /
   w_8005405C.c (flags1@0x0, flags2@0x4, field8/fieldC/field10/field14@0x8/0xC/0x10/0x14,
   field30..33@0x30..0x33) with the additional fields this function touches in the
   0x18-0x29 window. */

extern s32 D_80084850[];

extern void func_80055990(void *a0);
extern void func_800552C8(void);
extern void func_80054D64(void);

/* Resets global status and initializes two task objects with callbacks and defaults. */
void func_800559B4(void) {
    D_800847D0.flags00 = 0;
    D_800847D0.flags04 = 0;
    D_800847D0.flags00 = 0x10;
    D_800847D0.unk_1E = 0x5A;
    D_800847D0.unk_26 = -1;

    D_800847D0.unk_08 = 0;
    D_800847D0.unk_0C = 0;
    D_800847D0.unk_30 = 0;
    D_800847D0.unk_32 = 0;
    D_800847D0.unk_10 = 0;
    D_800847D0.unk_14 = 0;
    D_800847D0.unk_31 = 0;
    D_800847D0.unk_33 = 0;
    D_800847D0.unk_18 = 0;
    D_800847D0.unk_22 = 0;
    D_800847D0.unk_20 = 0;

    volumeScale[0] = 0x7FFF;
    volumeScale[1] = 0x7FFF;
    volumeScale[2] = 0x7FFF;

    D_80084850[0] = 0;
    func_80055990(&D_800848F8);

    func_80055990(&D_80084858);

    D_800848F8.callback = func_800552C8;
    D_800848F8.unk_08 = 0x64;
    D_800848F8.unk_0A = 0x64;
    D_800848F8.unk_12 = 0x50;
    D_800848F8.unk_14 = 2;

    D_80084858.callback = func_80054D64;
    D_80084858.unk_08 = 0x7F;
    D_80084858.unk_0A = 0x7F;
    D_80084858.unk_14 = 0x14;
    D_80084858.unk_12 = 0;

    D_800847D0.unk_28 = 0xC8;
}
