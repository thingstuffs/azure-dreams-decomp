#include "common.h"

extern s16 func_8009FB34(s32, s32);
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

/* Finds a valid neighboring direction and reports whether one was found. */
s32 func_800A0084(u8 *object, s16 *direction_out) {
    s32 direction = 0;
    s32 found;
    u16 *y_offsets = D_8006CCE8;
    u16 *x_offsets = D_8006CCD8;
    do {
        s16 neighbor;

        neighbor = func_8009FB34((object[0x24] + *x_offsets) & 0xFFFF, (object[0x25] + *y_offsets) & 0xFFFF);
        do {
        } while (0);
        y_offsets++;
        if (neighbor < 0) {
            goto next;
        }
        *direction_out = direction << 9;
        found = 1;
        goto done;
next:
        direction++;
        x_offsets++;
    } while (direction < 8);
    found = 0;
done:
    return found;
}
