#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
#include "engine/object/test_resident_bitmap_bit_api.h"                     /* extern */

/* Calls test_resident_bitmap_bit with 0x11FB. */
void test_resident_bit_11fb(void) {
    test_resident_bitmap_bit(Fp_far_kenkatyu);
}
