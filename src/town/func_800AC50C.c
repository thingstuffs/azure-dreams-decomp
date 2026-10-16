#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 testResidentBitmapBit();                     /* extern */

/* Passes 0x11FA to testResidentBitmapBit. */
void func_800A9C6C(void) {
    testResidentBitmapBit(0x11FA);
}
