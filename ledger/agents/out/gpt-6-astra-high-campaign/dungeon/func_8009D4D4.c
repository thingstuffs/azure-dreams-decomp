#include "common.h"

extern u32 D_80083460[];

/* Returns whether any of the state fields at offsets 0x0A, 0x0C, and 0x10 is nonzero. */
s32 func_800A2C34(void) {
    u32 *state;

    state = D_80083460;
    if (state[3] != 0 || state[4] != 0 || *(s16 *)((s8 *)state + 0xA) != 0) {
        return 1;
    }
    return 0;
}
