#include "common.h"

#include "engine/util.h"

#include "engine/audio/ram_block.h"

/* Sort up to 16 entries before the first zero key in ascending key order. */
void sort_entries_by_key(void)
{
    s32 saved_entry[2];
    s32 entry_count;
    s32 entry_index;
    s32 compare_index;
    SoundRamBlock *scan_entry;
    SoundRamBlock *entry;
    SoundRamBlock *entries;
    SoundRamBlock *compare_entry;
    SoundRamBlock *sort_entry;

    entry_count = 0;
    scan_entry = audio_ram_blocks;
    do {
        if (scan_entry->address.s != 0) {
            entry_count++;
            if (entry_count < 16) {
                scan_entry = scan_entry + 1;
                continue;
            }
        }
        break;
    } while (entry_count < 16);

    entry_index = 0;
    if (entry_count > 0) {
        entry = audio_ram_blocks;
        entries = entry;
        do {
            compare_index = entry_count - 1;
            if (entry_index < compare_index) {
                register s32 compare_offset;

                sort_entry = entry;
                for (; entry_index < compare_index; compare_index--) {
                    compare_offset = compare_index * 8;
                    compare_entry = (SoundRamBlock *)(compare_offset + (u8 *)entries);
                    compare_offset = sort_entry->address.s > compare_entry->address.s;
                    if (compare_offset != 0) {
                        saved_entry[1] = sort_entry->size;
                        saved_entry[0] = sort_entry->address.s;
                        sort_entry->size = compare_entry->size;
                        sort_entry->address.s = compare_entry->address.s;
                        compare_entry->size = saved_entry[1];
                        compare_entry->address.s = saved_entry[0];
                    }
                }
            }
            entry_index++;
            entry = entry + 1;
        } while (entry_index < entry_count);
    }
}
