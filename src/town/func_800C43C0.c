#include "common.h"

extern u16 D_800834B6;

/* mcard_end_check: return the masked 0x2000 flag from D_800834B6. */
s32 mcard_end_check(void) {
    return D_800834B6 & 0x2000;
}
