#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_80054C58.c,
   src/w_80055C50.c, src/w_8005440C.c, src/w_80054D64.c, src/w_800553D4.c, etc.):
   flags1@0x0, flags2@0x4, field8/fieldC/field10/field14/field18@0x8.. */

extern void func_80055D84(s16 param_0);

/* Reactivates the first locked channel and clears its lock flag. */
void func_80055CF4(void) {
    u32 channel;
    u32 channel_bit;
    u32 lock_bit;
    u32 lock_flags = D_800847D0.flags04 & 0xFF000000;

    for (channel = 0; channel < 4; channel++) {
        channel_bit = 0x1000000 << channel;
        lock_bit = channel_bit & 0xF000000;
        if (lock_flags & lock_bit) {
            func_80055D84((s16) channel);
            D_800847D0.flags04 &= ~lock_bit;
            break;
        }
    }
}
