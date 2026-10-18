#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void set_resident_bitmap_bit();                         /* extern */

/* Forwards a signed 16-bit value to set_resident_bitmap_bit. */
void func_80033B9C(s16 value) {
    set_resident_bitmap_bit(value);
}
