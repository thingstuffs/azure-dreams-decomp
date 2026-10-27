#include "common.h"
#include "engine/graphics.h"

/* Returns the first active record with the requested ID, or NULL at the end of the array. */
SpriteAttachment *find_flagged_record_by_id(SpriteAttachment *entry, u32 target_id) {
    for (;;) {
        if ((entry->flags & 0x20) && entry->id == target_id) {
            return entry;
        }
        if (entry->flags & 0x80) {
            break;
        }
        entry = (SpriteAttachment *)((u8 *)entry + 0xC);
    }
    return (SpriteAttachment *)0;
}
