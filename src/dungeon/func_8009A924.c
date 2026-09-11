#include "common.h"

extern s16 func_8009FB34(s32, s32);
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

/* Finds a valid neighboring direction and reports whether one was found. */
s32 func_800A0084(u8 *object, s16 *direction_out) {
    s32 direction;

    for (direction = 0; direction < 8; direction++) {
        if (func_8009FB34((object[0x24] + D_8006CCD8[direction]) & 0xFFFF,
                          (object[0x25] + D_8006CCE8[direction]) & 0xFFFF) >= 0) {
            *direction_out = direction << 9;
            return 1;
        }
    }
    return 0;
}
