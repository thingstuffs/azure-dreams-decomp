#include "common.h"

extern s16 D_800E3CCE;

/* Increment the counter up to 32 and report whether it advanced. */
s32 func_800A5690(void) {
    if (D_800E3CCE < 0x20) {
        D_800E3CCE++;
        return 1;
    }
    return 0;
}
