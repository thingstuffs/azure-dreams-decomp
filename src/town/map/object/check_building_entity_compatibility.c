#include "common.h"
#include "town/map/building_grid_g00638.h"

#include "engine/object/test_resident_bitmap_bit_api.h"
#include "town/map/object.h"
#include "town/menu/window.h"
#include "town/map/variant_data.h"

/* Checks whether a record can use an entity based on its kind and existing links. */
s32 check_building_entity_compatibility(s32 record_id, s32 entity_id)
{
    s32 slot_index;
    s32 entity_index;
    s32 record_index;
    s32 match_index;
    u8 record_kind;
    TownBuildingRecord *entity_base;
    TownBuildingRecord *entity;
    TownBuildingSlotRectangle *record_base;
    TownBuildingSlotRectangle *record;
    u8 *record_link_page;
    u8 *scan_link_page;
    u8 *slot;

    entity_base = town_building_records;
    entity_index = entity_id & 0xFF;
    entity = &entity_base[entity_index];
    if (test_resident_bitmap_bit(entity->availability_bit) == 0) {
        return 0;
    }

    record_base = town_building_slot_rectangles;
    record_index = record_id & 0xFF;
    record = record_base + record_index;
    if (record->width != entity->slot_width || record->height != entity->slot_height) {
        return 0;
    }

    record_link_page = (u8 *)0x80010000;
    if (record_link_page[((record_id & 0xFF) << 1) + 0x33A5] != 0) {
        return 0;
    }

    record_kind = record->kind;
    switch (record_kind) {
    case 0:
        return 0;

    case 1:
        if ((entity->kind & 1) == 0) {
            return 0;
        }

        slot_index = 0;
        scan_link_page = (u8 *)0x80010000;
        match_index = entity_index;
        do {
            slot = (u8 *)(((u32)(slot_index & 0xFF) << 1) + (unsigned long)scan_link_page);
            if (slot[0x33A4] == match_index || slot[0x33A5] == match_index) {
                return 0;
            }
            slot_index++;
        } while ((u32)(slot_index & 0xFF) < 0x21U);
        break;

    case 2:
    case 3:
    {
        s32 no_match;
        s32 other_entity_index;
        TownBuildingRecord *other_entity_base;
        TownBuildingRecord *other_entity;
        u8 *other_link_page;

        no_match = 0;
        other_entity_base = town_building_records;
        other_link_page = (u8 *)0x80010000;
        other_entity_index = other_link_page[((record_id & 0xFF) << 1) + 0x33A4];
        other_entity = &other_entity_base[other_entity_index];
        if (other_entity->linked_building_id != (entity_id & 0xFF)) {
            return no_match;
        }
        break;
    }

    default:
        break;
    }
    return 1;
}
