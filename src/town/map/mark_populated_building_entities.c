#include "common.h"
#include "town/map/building_grid_g00638.h"
#include "town/map.h"
#include "town/map/variant_data.h"
#include "town/menu/window.h"

extern void func_800B7B48(s16 x, s16 y, u8 entry_index);
/* Processes populated entity entries and sets their state field to 1. */
void mark_populated_building_entities(void)
{
    s32 entry_index = 0;
    TownBuildingRecord *entities = town_building_records;
    TownBuildingSlotRectangle *record = town_building_slot_rectangles;
    u8 *ram_page = (u8 *)0x80010000;
    u8 entity_id;

    do {
        entity_id = ram_page[(entry_index * 2) + 0x33A4];
        if (entity_id != 0) {
            s8 state_value;

            func_800B7B48(record->x, record->y,
                          entities[entity_id].tile_entry);
            entity_id = ram_page[(entry_index * 2) + 0x33A4];
            state_value = 1;
            entities[entity_id].marked = state_value;
        }
        record++;
        entry_index++;
    } while (entry_index < 0x21);
}
