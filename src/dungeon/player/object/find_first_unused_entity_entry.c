#include "common.h"
#include "dungeon/player/object.h"

extern u8 familiar_record_storage[];

/* Return the index of the first unused entry, or -1 if all entries are occupied. */
s32 find_first_unused_entity_entry(void)
{
    u8 *entry;
    s32 index;
    s32 result;

    index = 0;
    entry = familiar_record_storage;
    do {
        if (entry[0x13] == 0) {
            result = index;
            return result;
        }

        index++;
        entry += 0x8C;
        if (index >= 0x14) {
            break;
        }
    } while (1);

    result = -1;
    return result;
}
