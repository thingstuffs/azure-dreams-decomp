#include "common.h"
#include "town/scene.h"
#include "town/map/variant_data.h"

typedef void (*EntryCallback)(void *);

/* Copy each packed spawn entry, or let its source callback amend the current destination. */
void *populate_and_dispatch_entry_records(void *records, void *entries, s32 flags, s32 tag)
{
    TownSpawnEntry *record;
    TownSpawnEntry *entry;
    s32 record_flags;
    u32 tag_bits;
    u32 flag_bits;
    s32 header_word;
    u32 packed_word;
    s32 half_bits;

    /* BYTES: the original reuses the header constant register for the copy destination. */
    unsigned long header_or_addr;

    record = records;
    entry = entries;
    record_flags = flags;
    half_bits = record_flags >> 8;
    packed_word = record_flags & 0x3FFF0000;
    header_or_addr = 0xC0000010;
    header_word = packed_word | header_or_addr;
    half_bits &= 0x3F;
    flag_bits = half_bits << 24;
    tag &= 0xFF;
    tag_bits = tag << 16;
    header_or_addr = (unsigned long)record;
loop_0:
    {
        copy_words((s32 *)header_or_addr, (s32 *)entry, 5);
        if (record_flags != 0) {
            record->creation_argument = header_word;
        }
        packed_word = tag_bits | 0xC0000000;
        packed_word |= flag_bits & ~packed_word;
        half_bits = (u16)record->callback_id;
        record->callback_id = packed_word | half_bits;
        if ((u8)entry->active != 0) {
            ((EntryCallback)(unsigned long)(u32)entry->creation_argument)(record);
            entry++;
        } else {
            record++;
            entry++;
        }
        header_or_addr = (unsigned long)record;
    }
    if (entry[-1].flags != 0x80)
        goto loop_0;
    return record;
}
