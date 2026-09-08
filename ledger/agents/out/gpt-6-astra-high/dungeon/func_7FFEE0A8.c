#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s8 D_800FC418;

/* Clears D_800FC418 and returns 1. */
s32 func_8008B808(void) {
    D_800FC418 = 0;
    return 1;
}
