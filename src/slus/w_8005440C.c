#include "shared/sound_state.h"
#include "common.h"

/* Sibling struct (matches src/w_80054C58.c's SoundPlaybackState exactly for the
 * fields touched here): flags1 at 0x0, flags2 at 0x4. */

/* Opaque state-block struct: only its address is taken here (never
 * dereferenced), but sibling functions in this wave show a function-pointer
 * field at 0x0, an s32 flag/counter at 0x4, and an s16 timer at 0x8. Declared
 * >8 bytes to force %hi/%lo addressing. */


extern void func_800550E8(void);
extern s32 func_80059D60(void);
extern s32 func_800545F4(SoundTask *a0);
extern void func_800553D4(s32 a0);
extern void func_80054538(SoundTask *a0);

/* Handles flag-triggered events and status checks, then dispatches the state block. */
void func_8005440C(void) {
    if (D_800847D0.flags04 & 0x2) {
        func_800550E8();
    }

    if (D_800847D0.flags00 & 0x100) {
        if (func_80059D60() == 3 || func_800545F4(&D_800848F8) == -1) {
            func_800553D4(0x71);
        }
    }

    func_80054538(&D_800848F8);
}
