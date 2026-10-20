#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
#include "engine/object/test_resident_bitmap_bit_api.h"                     /* extern */

/* Passes 0x11FA to test_resident_bitmap_bit. */
void test_resident_bit_11fa(void) {
    test_resident_bitmap_bit(0x11FA);
}
