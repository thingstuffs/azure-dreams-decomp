#include "modules/dungeon_dungeon_setup.h"

void initKohPropertiesAndEntryTables(void)
{
    s32 slot_index;
    volatile u8 *clear_ptr;
    s32 source_offset;
    dungeon_setup_80284068_Entry *init_entry;
    dungeon_setup_80284068_Entry **table_slot;
    int entry_page_offset;
    u8 *table_base;
    u8 *entries_base;
    slot_index = 3;
    clear_ptr = (u8 *) 0x80010006;
    {
        u8 *state_base = (u8 *) 0x80010000;
        state_base[0x2194] = 5;
        state_base[0x21BA] = 5;
        state_base[0x2195] = 4;
        state_base[0x21BB] = 4;
        state_base[0x2196] = 4;
        state_base[0x2197] = 100;
        state_base[0x2199] = 16;
        state_base[0x21BC] = 16;
        *((s16 *) (state_base + 0x219A)) = 16;
        state_base[0x21A5] = 1;
        *((s32 *) (state_base + 0x21A8)) = 0x6000;
        *((s32 *) (state_base + 0x21B0)) = 0x6000;
        state_base[0x21A7] = 0;
        *((s32 *) (state_base + 0x21AC)) = 0;
        *((s16 *) (state_base + 0x21B4)) = 0;
        *((s16 *) (state_base + 0x21B6)) = 0;
        *((s16 *) (state_base + 0x21BE)) = 0x400;
    }
    do {
        clear_ptr[0x21C0] = 0;
        clear_ptr[0x21C1] = 0;
        clear_ptr -= 2;
    }
    while ((--slot_index) >= 0);
    slot_index = 19;
    entry_page_offset = 0x3E48;
    {
        u8 *ram_page = (u8 *) 0x80010000;
        ram_page[0x21E0] = 0xFF;
        ram_page[0x21E1] = 0xFF;
        *((s32 *) (ram_page + 0x21E4)) = 0;
    }
    do {
    init_entry = &((dungeon_setup_80284068_Entry *)D_800E3E48)[slot_index];
    table_slot = &((dungeon_setup_80284068_Entry **)D_800E3DF0)[slot_index];
    source_offset = slot_index * 0x54;
    restoreActorStatsFromSnapshot(init_entry, (void *) (0x800102F0 + source_offset));

    *table_slot = init_entry;
    } while ((--slot_index) >= 0);
    slot_index = 19;
    {
        volatile u8 *index_ptr = (u8 *) 0x80010013;
        u8 *copy_table_base = D_800E3DF0;
        dungeon_setup_80284068_Entry **copy_table_slot = (dungeon_setup_80284068_Entry **) (copy_table_base + 0x4C);
        u8 *ram_page = (u8 *) 0x800E0000;
        u8 *copy_entries_base = ram_page + entry_page_offset;
        dungeon_setup_80284068_Entry *copy_entry = (dungeon_setup_80284068_Entry *) (copy_entries_base + 0xA64);
        u8 *copy_dest;
        dungeon_setup_80284068_CursorPtr word_cursor;
        copy_dest = (u8 *) 0x80010A64;
        word_cursor.raw = (u8 *) 0x80010050;
        do {
            word_cursor.entry->dest = word_cursor.entry->src;
            index_ptr[0x2238] = getBoundedStrideIndex(word_cursor.entry->arg, (void *) 0x80010248, 4, 20);
            *((dungeon_setup_80284068_Entry *) (copy_dest + 0x2260)) = *copy_entry;
            index_ptr[0x224C] = getBoundedStrideIndex(*copy_table_slot, ram_page + 0x3E48, 0x8C, 20);
            copy_table_slot--;
            copy_entry--;
            copy_dest -= 0x8C;
            word_cursor.raw -= 4;
            index_ptr--;
        }
        while ((--slot_index) >= 0);
    }
    {
        u8 *ram_page = (u8 *) 0x80010000;
        *((s32 *) (ram_page + 0x2D58)) = 0;
        *((s16 *) (ram_page + 0x2D50)) = 0;
    }
}
