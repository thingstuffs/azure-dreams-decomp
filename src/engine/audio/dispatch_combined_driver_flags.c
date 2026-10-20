#include "common.h"

extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[64];
extern void func_8005E97C(s32 key_on, s32 voices);

/* Combines flags from D_80073740 and passes them to func_8005E97C. */
void dispatch_combined_driver_flags(void) {
    s32 flags;
    s32 flag_index;

    flags = 0;
    for (flag_index = 0; flag_index < audio_voice_count[0]; flag_index++) {
        flags |= audio_voice_masks[flag_index];
    }
    func_8005E97C(0, flags);
}
