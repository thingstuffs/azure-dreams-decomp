#include "common.h"
#include "shared/game_state.h"
#include "town/map/building_grid_g00638.h"
#include "engine/object.h"
#include "town/map/variant_data.h"
#include "town/menu/window.h"

/* CheckBuildBuildingLandNo collects eligible land slots for a building and returns their count. */
s32 CheckBuildBuildingLandNo(record_key, slots_out)
u8 record_key;
s8 *slots_out;
{
    s8 *slots_start;
    TownBuildingRecord *record;
    u8 slot_count;
    s32 slot;
    s32 record_id;
    s32 slot_index;
    u32 first_id;
    u32 second_id;
    u8 single_id;
    u8 *slot_pair;
    TownBuildingSlotRectangle *entry;
    TownBuildingRecord *match_record;
    TownBuildingRecord *match_records;

    slot_count = 0;
    {
        TownBuildingRecord *records = town_building_records;
        record = records + (record_key & 0xFF);
    }
    slots_start = slots_out;
    if (test_resident_bitmap_bit(record->availability_bit) == 0) {
        return 0;
    }

    switch (record->kind) {
    case 4:
    case 8:
    {
        u8 *slot_table_base;
        u8 *slot_row;
        u32 selected_id;

        TownBuildingRecord *records = town_building_records;
        selected_id = record_key & 0xFF;
        if (records[selected_id].partner_building_id == 0) {
            break;
        }
        slot_table_base = (u8 *)0x80010000;
        slot = 0;
        do {
            slot_row = (u8 *)((u8)slot * 2 + (unsigned long)slot_table_base);
            if ((slot_row[0x33A4] == records[selected_id].partner_building_id) &&
                (slot_row[0x33A5] != selected_id)) {
                *slots_out++ = slot;
                slot_count++;
            }
            slot++;
        } while ((u8)slot < 0x21);
        *slots_out = 0;
        return (u8)slot_count;
    }
    case 16:
    {
        TownBuildingRecord *records = town_building_records;
        s32 entry_id = record_key & 0xFF;
        single_id = records[entry_id].partner_building_id;
        if (single_id == 0)
            break;
        if (GAME_STATE->building_slots[33][0] == single_id) {
            if (GAME_STATE->building_slots[33][1] != entry_id) {
                *slots_out++ = 0xB;
                slot_count++;
            }
        }
        break;
    }
    case 1:
    {
        TownBuildingSlotRectangle *entries;
        u8 *slots_page;
        s32 excluded_id = 0;
        slot = 0;
        slots_page = (u8 *)0x80010000;
        entries = &town_building_slot_rectangles[0];
        record_id = record_key & 0xFF;
        match_records = town_building_records;
        match_record = match_records + record_id;
        do {
            slot_index = slot & 0xFF;
            slot_pair = (u8 *)(slot_index * 2 + (unsigned long)slots_page);
            first_id = slot_pair[0x33A4];
            if (first_id == record_id || (second_id = slot_pair[0x33A5], second_id == record_id)) {
                slots_out = slots_start;
                slot_count = 0;
                break;
            }
            entry = (TownBuildingSlotRectangle *)(slot_index * 8 + (unsigned long)entries);
            if (entry->width == match_record->slot_width &&
                entry->height == match_record->slot_height &&
                first_id >= 0x2D) {
                excluded_id = 0x30;
                if (first_id != excluded_id && second_id == 0) {
                    *slots_out++ = slot;
                    slot_count++;
                }
            }
            slot++;
        } while ((u8)slot < 0x21);
        break;
    }
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    default:
        break;
    }
    *slots_out = 0;
    return (u8)slot_count;
}
