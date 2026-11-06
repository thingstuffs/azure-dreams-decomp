#include "common.h"
#include "engine/scene.h"

typedef struct SpriteAttachmentEntry {
    /* 0x0 */ u8 flags;
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} SpriteAttachmentEntry; /* size 0xC */

/* Return the last ID match with flag 0x20 (or NULL) and subtract half the entry count from its index (or zero). */
SpriteAttachmentEntry *find_last_flagged_record_by_id(SpriteAttachmentEntry *entry, s32 want, u16 *idx_out)
{
    u32 entry_count;
    SpriteAttachmentEntry *match_address;
    u8 entry_flags;

    match_address = 0;
    *idx_out = 0;
    entry_count = 0;

    do {
        if (entry->flags & 0x20) {
            if (entry->id == want) {
                match_address = entry;
                *idx_out = entry_count;
            }
        }
        entry_count++;
        entry_flags = entry->flags;
        entry++;
    } while (!(entry_flags & 0x80));

    *idx_out = *idx_out - (entry_count >> 1);
    return match_address;
}
