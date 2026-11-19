#include "common.h"
#include "frontend/card.h"


/* Returns the first signed word of the indexed 128-byte record. */
s32 card_dev_get_slot_marker(s32 record_index) {
    return card_slot_header_cache[record_index].fields.marker;
}
