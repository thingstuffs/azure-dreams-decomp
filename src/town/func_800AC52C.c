#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 testResidentBitmapBit();                     /* extern */

/* Calls testResidentBitmapBit with 0x11FB. */
void func_800A9C8C(void) {
    testResidentBitmapBit(0x11FB);
}
