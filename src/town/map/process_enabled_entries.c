#include "script_symbols.h"
#include "town/map/building_grid_g00638.h"
#include "common.h"
#include "m2c_compat.h"
#include "engine/cd.h"
#include "engine/object.h"
#include "slus.h"
#include "town/map.h"
#include "town/map/position.h"
#include "town/map/variant_data.h"
#include "town/menu/window.h"

extern u32 D_800D1BF4[2];

typedef struct S_800B98B4_3 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
} S_800B98B4_3;

/* Read the town building data, then apply each slot's building tile entry and track type-1 entries. */
void load_and_apply_town_building_tiles(void) {
    S_800B98B4_3 *state_base;
    TownBuildingSlotRectangle *slot_data;
    TownBuildingRecord *entry_table;
    s32 slot_index;
    u8 entry_id;
    TownBuildingRecord *entry;
    TownBuildingRecord *reloaded_entry;

    Control_CD(6, D_800D1BF4, 0);
    slot_index = 0;
    drain_cd_command_queue();
    clear_resident_bitmap_bit(F_funsui_sound);
    entry_table = town_building_records;
    slot_data = town_building_slot_rectangles;
    state_base = (S_800B98B4_3 *)0x80010000;
    do {
        entry_id = ((S_800B98B4_3 *)((u8 *)state_base + (slot_index * 2)))->unk_33A4;
        if (entry_id != 0) {
            entry = (TownBuildingRecord *)(entry_id * sizeof(*entry) + (unsigned long)entry_table); /* BYTES: retail adds the table base to the scaled row offset. */
            if (entry->tile_entry_enabled != 0) {
                apply_building_tile_entry(slot_data->x, slot_data->y, entry->tile_entry);
            }
            entry_id = ((S_800B98B4_3 *)((u8 *)state_base + (slot_index * 2)))->unk_33A4;
            reloaded_entry = (TownBuildingRecord *)(entry_id * sizeof(*reloaded_entry) + (unsigned long)entry_table); /* BYTES: retail adds the table base to the reloaded row offset. */
            if (reloaded_entry->tile_entry == 1) {
                set_resident_bitmap_bit(F_funsui_sound);
            }
        }
        slot_data++;
        slot_index += 1;
    } while (slot_index < 0x21);
}
