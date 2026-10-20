#include "common.h"

#include "common.h"
#include "shared/resident_resources.h"


extern ResidentBitmapEntry resident_bitmap_key_map[];
extern void set_resident_bitmap_bit(s32 bit_id);

/* Pass each matching key's value to set_resident_bitmap_bit. */
void set_resident_bits_for_matching_key(s16 key) {
    ResidentBitmapEntry *entry = resident_bitmap_key_map;

    if (entry->key != 0) {
        do {
            if (key == entry->key) {
                set_resident_bitmap_bit(entry->value);
            }
            entry++;
        } while (entry->key != 0);
    }
}
