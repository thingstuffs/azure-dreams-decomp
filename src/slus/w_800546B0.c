#include "shared/sound_state.h"
#include "common.h"

/* The shared task record is passed to the pending-read check. */

/* Declared as an array (>8B) so gcc emits %hi/%lo addressing (lui+lw), matching
 * the target's lui v1,%hi(D_800847DC); lw v1,%lo(D_800847DC)(v1) sequence. */
extern u32 D_800847DC[3];

extern int func_80053D64(void);
extern int func_800545F4(SoundTask *a0);
extern void func_80054E00(s32 a0);

/* Fires event 0x74 when the CD read position reaches its target or the pending read check fails. */
void func_800546B0(void) {
    if ((u32)func_80053D64() < D_800847DC[0]) {
        if (func_800545F4(&D_80084858) == -1) {
            func_80054E00(0x74);
        }
    } else {
        func_80054E00(0x74);
    }
}
