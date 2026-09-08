#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 D_80100D94[];
/* came_bright_set: Set camera brightness. */
void func_800A48A4(u32 brightness) {
    *D_80100D94 = brightness;
}
