#include "common.h"

extern u8 runtime_dispatch_mode_alias[];

/* Return the current value capped at 40 when the mode is 2, or zero otherwise. */
s32 read_capped_audio_meter(void)
{
    if (runtime_dispatch_mode_alias[0] == 2) {
        s32 capped_value = 0x28;
        s32 current_value = *(s16 *)0x8008146C;

        if (current_value < 0x29) {
            capped_value = current_value;
        }
        return capped_value;
    }
    return 0;
}
