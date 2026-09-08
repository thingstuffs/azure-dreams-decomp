#include "common.h"

#include "common.h"

extern u16 D_80080AD4;
extern u8 D_8008395C[9];

/* Returns the stored flags with bit 2 set when D_80080AD4 is nonzero. */
s32 func_8003F5AC(void) {
    s32 flags = D_8008395C[0];

    if (D_80080AD4 != 0) {
        flags |= 4;
    } else {
        flags &= 0xFF;
    }
    return flags;
}
