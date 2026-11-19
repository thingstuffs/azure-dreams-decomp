#include "common.h"
#include "frontend/card.h"

/* Count nonzero heads in the five 0x80-byte slots. */
s32 card_dev_count_cached_slots(void) {
    s32 count;
    s32 index;
    s32 slot_head;

    count = 0;
    index = 0;
    do {
        slot_head = card_slot_header_cache[index].fields.marker;
        index++;
        if (slot_head != 0) {
            count++;
        }
    } while (index < 5);

    return count;
}
