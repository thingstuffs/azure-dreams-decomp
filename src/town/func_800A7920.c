#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80100DE0[];
extern u8 D_80100D98[];
void func_800A5080(void) {
    *D_80100DE0 = (s32) D_80100D98;
}
