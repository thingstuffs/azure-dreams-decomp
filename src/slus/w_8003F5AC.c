#include "slus/cd_cohort_types.h"


/* Returns the stored flags with bit 2 set when D_80080AD4 is nonzero. */
s32 func_8003F5AC(void) {
    s32 flags = D_80083958[0].unk4;

    if (D_80080AD4 != 0) {
        flags |= 4;
    } else {
        flags &= 0xFF;
    }
    return flags;
}
