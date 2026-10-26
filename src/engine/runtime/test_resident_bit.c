#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/runtime.h"

// Forwards a signed 16-bit value to test_resident_bitmap_bit.
s32 test_resident_bit(s16 value) {
    return test_resident_bitmap_bit(value);
}
