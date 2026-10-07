#include "shared/sound_state.h"
#include "common.h"
#include "shared/sound_volume.h"

/* Canonical "task/timer object" struct shared with func_80055990's own SoundTask
   (src/code.c) and w_800540A8.c's SoundTask / w_80054C58.c's SoundTask: field0 is
   a function pointer, followed by s16 field8/fieldA, s32 fieldC, then more s16 fields. */

/* Canonical status-block struct at D_800847D0, established in w_800540A8.c / w_80054C58.c /
   w_8005405C.c / w_800559B4.c: flags1@0x0, flags2@0x4, field8/fieldC/field10/field14@0x8/0xC/
   0x10/0x14, field18-33 across the tail. */


extern s32 func_80055750(s16 channel_level);
extern void func_8005B27C(s16 a0, s32 a1, s32 a2);

/* Scale and clamp the output value when enabled, then apply it to both channels. */
void func_800552C8(void)
{
    s32 scale_product;
    s32 scaled_value;
    s16 channel_value;

    if (D_800847D0.flags00 & 0x100) {
        scale_product = D_800848F8.unk_08 * volumeScale[1];
        scaled_value = (s16) (scale_product / 32767);
        scaled_value = scaled_value * D_800848F8.unk_10;
        channel_value = func_80055750((s16) (scaled_value / 128));
        func_8005B27C(D_800847D0.unk_22, channel_value, channel_value);
    }
}
