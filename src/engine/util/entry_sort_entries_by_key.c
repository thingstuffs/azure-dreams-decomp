#include "common.h"
#include "engine/util.h"
#include "slus/data.h"
#include "engine/audio/ram_block.h"

extern u8 sound_ram_reserve_mode[9];

/* Reserves space in the entry table and returns its offset, or -1 if it exceeds the limit. */
s32 reserve_sound_ram_region(s32 size)
{
    s32 alloc_size;
    s32 offset;
    SoundRamBlock *first_entry;
    s32 initial_end;
    s32 *reserve_sizes;
    s32 alloc_limit;
    s32 end_offset;
    SoundRamBlock *entry;
    s32 reserved_size;
    s32 entry_index;
    u8 reserve_index;

    alloc_size = size;
    offset = 0x1010;
    first_entry = &audio_ram_blocks[0];
    if (first_entry->address.s != 0) {
        goto loop_start;
    }
    initial_end = alloc_size + 0x1010;
    {
        u8 initial_reserve_index = sound_ram_reserve_mode[0];
        s32 *initial_reserve_sizes = sound_ram_reserved_sizes;

        alloc_limit = 0x80000 - initial_reserve_sizes[initial_reserve_index];
    }
    if ((u32)initial_end >= (u32)alloc_limit) {
        return -1;
    }
    first_entry->address.s = offset;
    first_entry->size = alloc_size;
    goto tail;

found:
    entry->address.s = end_offset;
    entry->size = alloc_size;
    sort_entries_by_key();
    return offset;

loop_start:
    {
        s32 memory_end;

        entry_index = 0;
        memory_end = 0x80000;
        entry = first_entry;
        reserve_index = sound_ram_reserve_mode[0];
        for (; 16 > entry_index; entry_index++, entry++) {
            if (entry->size != 0) {
                continue;
            }
            reserved_size = (reserve_sizes = sound_ram_reserved_sizes)[reserve_index];
            offset = entry->address.s;
            end_offset = offset + alloc_size;
            if ((u32)end_offset >= (u32)(memory_end - reserved_size)) {
                return -1;
            }
            goto found;
        }
    }

tail:
    sort_entries_by_key();
    return offset;
}
