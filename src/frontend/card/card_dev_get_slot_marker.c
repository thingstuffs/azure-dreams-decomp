#include "common.h"

extern u8 D_8009DDD8[];

/* Returns the first signed word of the indexed 128-byte record. */
s32 card_dev_get_slot_marker(s32 record_index) {
    return *(s32 *)(D_8009DDD8 + (record_index << 7));
}
