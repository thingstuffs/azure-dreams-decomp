#include "common.h"

/* Set state bytes from flags, giving lower bits priority within each pair. */
void func_800970AC(s32 flags, u8 *state) {
    if (flags & 1) {
        state[0x37] = 1;
    } else {
        if (flags & 0x10) {
            state[0x36] = 1;
        }
    }
    if (flags & 0x100) {
        state[0x39] = 1;
        return;
    }
    if (flags & 0x1000) {
        state[0x38] = 1;
    }
}
