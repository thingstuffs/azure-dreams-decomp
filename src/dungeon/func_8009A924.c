#include "common.h"
#include "shared/dir_step.h"

extern s16 func_8009FB34(s32, s32);

/* Finds a valid neighboring direction and reports whether one was found. */
s32 func_800A0084(u8 *object, s16 *direction_out) {
    s32 direction;

    for (direction = 0; direction < 8; direction++) {
        if (func_8009FB34((object[0x24] + ((u16 *)dirStepX)[direction]) & 0xFFFF,
                          (object[0x25] + ((u16 *)dirStepY)[direction]) & 0xFFFF) >= 0) {
            *direction_out = direction << 9;
            return 1;
        }
    }
    return 0;
}
