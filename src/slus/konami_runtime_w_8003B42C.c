#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void set_resident_bitmap_bit();                     /* extern */
void clear_resident_bitmap_bit();                     /* extern */

/* Selects which runtime call receives 1000 and which receives 10. */
void func_8003B42C(s32 mode) {
    if (mode != 0) {
        set_resident_bitmap_bit(0x3E8);
        clear_resident_bitmap_bit(0xA);
        return;
    }
    clear_resident_bitmap_bit(0x3E8);
    set_resident_bitmap_bit(0xA);
}
