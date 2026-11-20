#include "common.h"
#include "town/map/building_grid_g00638.h"
#include "town/map.h"
#include "town/map/variant_data.h"
#include "town/menu.h"

extern TownRectangle D_800D43F0;

typedef struct S_800B8248_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
} S_800B8248_0;

/* Initializes the default region and processes each occupied resource slot. */
void initialize_building_region_resources(void) {
    s32 region_x;
    s32 region_y;
    s32 region_width;
    s32 region_height;
    s32 slot_index;
    s32 slot_counter;
    u8 resource_index;
    TownBuildingRecord *resources;
    void *state_base;
    S_800B8248_0 *slot;
    TownBuildingSlotRectangle *region;

    reset_script_rect_list();
    append_scaled_rect_to_script_list(0x3FU, 0U, 0x10U, 0x10U, &D_800D43F0);
    slot_counter = 0;
    state_base = (void *)0x80010000;
    resources = town_building_records;
    do {
        slot_index = slot_counter & 0xFF;
        slot = (void *)((slot_index * 2) + (long)state_base);
        resource_index = slot->unk_33A4;
        if (resource_index != 0) {
            resources[resource_index].marked = 1;
            region = &town_building_slot_rectangles[slot_index];
            region_x = region->x;
            region_y = region->y;
            region_width = region->width;
            region_height = region->height;
            resource_index = slot->unk_33A4;
            append_scaled_rect_to_script_list(region_x, region_y, region_width, region_height,
                          &town_building_records[resource_index].position_entry);
        }
        slot_counter += 1;
    } while ((u32)(u8)slot_counter < 0x21U);
    create_entry_builder_controller();
}
