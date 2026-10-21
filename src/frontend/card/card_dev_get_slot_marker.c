#include "common.h"
#include "frontend/card.h"

extern u8 card_slot_header_cache[];

/* Returns the first signed word of the indexed 128-byte record. */
s32 card_dev_get_slot_marker(s32 record_index) {
    return *(s32 *)(card_slot_header_cache + (record_index << 7));
}
