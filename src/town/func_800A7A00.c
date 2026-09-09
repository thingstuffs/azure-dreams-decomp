#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80100E10;

/* tcame_chase_fix: set the camera chase fix value. */
void tcame_chase_fix(s32 value) {
    D_80100E10 = value;
}
