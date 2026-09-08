#include "common.h"

extern u8 D_80081485;

/* Returns whether D_80081485 is zero. */
s32 func_800B14CC(void) {
    return D_80081485 == 0;
}
