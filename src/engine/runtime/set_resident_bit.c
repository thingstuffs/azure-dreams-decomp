#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/runtime.h"

/* Forwards a signed 16-bit value to set_resident_bitmap_bit. */
void set_resident_bit(s16 value) {
    set_resident_bitmap_bit(value);
}
