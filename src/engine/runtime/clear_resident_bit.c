#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/runtime.h"

/* Forward a signed 16-bit value to clear_resident_bitmap_bit. */
void clear_resident_bit(s16 value) {
    clear_resident_bitmap_bit(value);
}
