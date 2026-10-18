#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 test_resident_bitmap_bit();                     /* extern */

/* Calls test_resident_bitmap_bit with 0x11FB. */
void func_800A9C8C(void) {
    test_resident_bitmap_bit(0x11FB);
}
