#include "common.h"

extern s32 func_800A0818(u8, u8, u8, u8, s32 *);
extern u8 *D_80175D50;
extern u8 D_80082E80[];

/* Returns the signed coordinate calculation result scaled down by nine bits. */
s32 func_801704BC(void) {
    s32 value;
    u8 *state;

    state = *(u8 **)(D_80175D50 + 0xC);
    return (func_800A0818(state[0x24], state[0x25], D_80082E80[0x24],
                           D_80082E80[0x25], &value) << 0x10) >> 0x19;
}
