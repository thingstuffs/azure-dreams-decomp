#include "common.h"

#include "common.h"
#include "shared/resident_resources.h"
#include "engine/object.h"
#include "slus/data.h"

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
