#include "common.h"
#include "shared/resident_resources.h"
#include "town/map.h"
#include "town/menu.h"

extern void **scale_coordinates_and_append_pointers();
extern u8 town_building_records[];
extern u8 town_building_slot_rectangles[];
extern u8 D_800D43F0[];

typedef struct S_800B8248_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
} S_800B8248_0;

typedef struct S_800B8248_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800B8248_1;

/* Initializes the default region and processes each occupied resource slot. */
void initialize_building_region_resources(void) {
    s32 region_x;
    s32 region_y;
    s32 region_width;
    s32 region_height;
    s32 slot_index;
    s32 slot_counter;
    u8 resource_index;
    u8 *resources;
    void *state_base;
    S_800B8248_0 *slot;
    S_800B8248_1 *region;

    initialize_shared_script_data();
    scale_coordinates_and_append_pointers(0x3FU, 0U, 0x10U, 0x10U, D_800D43F0);
    slot_counter = 0;
    state_base = (void *)0x80010000;
    resources = town_building_records;
    do {
        slot_index = slot_counter & 0xFF;
        slot = (void *)((slot_index * 2) + (long)state_base);
        resource_index = slot->unk_33A4;
        if (resource_index != 0) {
            ((ResourceSlotStateView *)((void *)((resource_index << 5) + (long)resources)))->unk_0A = 1;
            region = (slot_index * 8) + town_building_slot_rectangles;
            region_x = region->unk_00;
            region_y = region->unk_01;
            region_width = region->unk_02;
            region_height = region->unk_03;
            resource_index = slot->unk_33A4;
            scale_coordinates_and_append_pointers(region_x, region_y, region_width, region_height,
                          (resource_index << 5) + (town_building_records + 0xC));
        }
        slot_counter += 1;
    } while ((u32)(u8)slot_counter < 0x21U);
    create_entry_builder_controller();
}
