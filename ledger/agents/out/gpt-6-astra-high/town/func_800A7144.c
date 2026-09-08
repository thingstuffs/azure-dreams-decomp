#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 D_80100D94[];
/* Stores the value in D_80100D94. */
void func_800A48A4(u32 value) {
    *D_80100D94 = value;
}
