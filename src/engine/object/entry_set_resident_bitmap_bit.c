#include "common.h"

#include "common.h"
#include "shared/resident_resources.h"


extern ResidentBitmapEntry D_8006A94C[];
extern void set_resident_bitmap_bit(s32 bit_id);

/* Pass each matching key's value to set_resident_bitmap_bit. */
void func_80035D4C(s16 key) {
    ResidentBitmapEntry *entry = D_8006A94C;

    if (entry->key != 0) {
        do {
            if (key == entry->key) {
                set_resident_bitmap_bit(entry->value);
            }
            entry++;
        } while (entry->key != 0);
    }
}
