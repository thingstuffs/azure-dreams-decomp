#include "common.h"

extern s32 D_80100D20;

/* Clears D_80100D20. */
void clear_global_80100_d_20(void) {
    D_80100D20 = 0;
}
