#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80100E10;

/* tcame_chase_fix_reset: clear the camera chase fix value. */
void func_800A516C(void) {
    D_80100E10 = 0;
}
