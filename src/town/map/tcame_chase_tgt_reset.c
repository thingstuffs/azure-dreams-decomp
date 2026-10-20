#include "common.h"

extern s32 D_80100DE0[];
extern u8 D_80100D98[];
/* tcame_chase_tgt_reset: Reset the camera chase target to D_80100D98. */
void tcame_chase_tgt_reset(void) {
    *D_80100DE0 = (s32) D_80100D98;
}
