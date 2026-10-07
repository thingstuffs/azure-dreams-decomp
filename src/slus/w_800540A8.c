#include "shared/sound_state.h"
#include "common.h"

/* callee: task/timer-like initializer, already matched in src/code.c */

extern void func_80055990(SoundTask *a0);
extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);


/* Sibling struct for D_800847D0: fields cleared here are a subset of a larger
   object; layout inferred purely from the offsets this function touches. */


/* Resets the audio command state and task object, then clears playback status fields. */
void func_800540A8(void) {
    func_8005A4E8(0, 0, 0);
    func_80055990(&D_80084858);

    ((s32)D_800847D0.unk_08) = 0;
    ((s32)D_800847D0.unk_0C) = 0;
    D_800847D0.unk_30 = 0;
    D_800847D0.unk_32 = 0;
    ((s32)D_800847D0.unk_10) = 0;
    ((s32)D_800847D0.unk_14) = 0;
    D_800847D0.unk_31 = 0;
    D_800847D0.unk_33 = 0;
    ((s32)D_800847D0.unk_18) = 0;
}
