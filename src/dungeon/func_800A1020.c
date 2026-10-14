#include "common.h"

extern s8 D_80080A88;   /* keep-floor-music flag; declared scalar as in func_80087A70, func_802833F4, func_80084340 and the town readers */

/* Preserve the sound sequence for tutorial mode or within a normal floor group. */
s32 func_800A6780(void) {
    s32 *stateBase = (s32 *)0x80010000;   /* integer page, two genuine reads (decision 44) */
    s32 mode;
    s32 boundaryValue;

    mode = stateBase[0x2090 / 4];
    D_80080A88 = 0;
    if (mode == 1 || (mode == 0 &&
        (boundaryValue = stateBase[0x234 / 4],
         boundaryValue / 5 == (boundaryValue + 1) / 5))) {
        D_80080A88 = 1;
        return 1;
    }
    return 0;
}
