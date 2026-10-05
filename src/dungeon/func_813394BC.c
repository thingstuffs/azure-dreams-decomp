#include "common.h"
#include "shared/tile_object.h"

extern s32 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern u8 *D_80175D50;

/* Returns the signed coordinate calculation result scaled down by nine bits. */
s32 func_801704BC(void) {
    s32 value;
    u8 *state;

    state = *(u8 **)(D_80175D50 + 0xC);
    return (func_800A0818(state[0x24], state[0x25], D_80082E80.tileX,
                          D_80082E80.tileY, &value) << 0x10) >> 0x19;
}
