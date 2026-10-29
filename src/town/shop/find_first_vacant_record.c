#include "common.h"
#include "town/shop/item_lookup.h"
#include "town/shop.h"

/* Find the first vacant record among count records of size 0x54. */
s32 find_first_vacant_record(const u8 *records, s32 count) {
    s32 index;
    for (index = 0; index < count; index++, records += 0x54) {
        if (records[0x13] == 0) {
            return index;
        }
    }
    return -1;
}
