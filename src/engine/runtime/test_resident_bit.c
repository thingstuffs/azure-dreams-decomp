#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 test_resident_bitmap_bit();                         /* extern */

// Forwards a signed 16-bit value to test_resident_bitmap_bit.
void test_resident_bit(s16 value) {
    test_resident_bitmap_bit(value);
}
