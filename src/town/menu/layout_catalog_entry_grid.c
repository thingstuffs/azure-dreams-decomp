#include "common.h"
#include "shared/object_payload.h"
#include "town/menu/catalog_parts.h"
#include "town/menu.h"

typedef struct TownInitialPosition {
    void *data;
    u16 x;
    u16 y;
} TownInitialPosition;

extern TownInitialPosition catalog_grid_layout[5];
extern s8 D_80128614[];
extern s8 catalog_grid_packets[];

/* Initialize town object data, grid positions, and display dimensions. */
void layout_catalog_entry_grid(void)
{
    s32 object_index;
    TownInitialPosition *initial_pos;
    s8 *group_data;
    s8 *entry_data;
    s16 detail_y;
    s32 row_offset;
    s32 row;
    s32 column_offset;
    s32 column;
    s32 object_offset;
    s32 initial_index;
    s32 final_width;
    s32 final_x;
    u16 initial_y;
    ItemMenuPart *object;
    ItemMenuPartPosition *position;
    ItemMenuPart **display_slot;
    ItemMenuPart **initial_slot;
    ItemMenuPart **entry_slot;
    ItemMenuPart **group_slot;

    object_index = 0x1C;
    initialize_catalog_entry_packets();
    initial_index = 0;
    {
        ItemMenuPart **object_base;
        object_base = catalog_display_node_slots;
        initial_slot = &object_base[0x1C];
    }
    initial_pos = catalog_grid_layout;
initial_loop:
    (*initial_slot)->handler = initial_pos->data;
    object = *initial_slot;
    initial_index += 1;
    object->position->x = initial_pos->x;
    object_index += 1;
    object = *initial_slot;
    initial_y = initial_pos->y;
    initial_pos += 1;
    object->position->y = initial_y;
    initial_slot += 1;
    if (initial_index < 5) {
        goto initial_loop;
    }

    initial_index = 0;
    group_data = catalog_grid_packets;
    {
        ItemMenuPart **object_base;
        object_base = catalog_display_node_slots;
        object_offset = object_index << 2;
        group_slot = (ItemMenuPart **)(object_offset + (u8 *)object_base);
    }
    do {
        object = *group_slot;
        column_offset = initial_index >> 3;
        object->handler = group_data;
        object = *group_slot;
        column_offset <<= 7;
        object->position->x = column_offset + 0x38;
        row_offset = (initial_index & 7) * 0x12;
        (*group_slot)->position->y = row_offset + 0x2C;
        group_slot += 1;
        (*group_slot)->position->x = column_offset + 0x3E;
        object_index += 3;
        object = *group_slot;
        detail_y = row_offset + 0x30;
        position = object->position;
        group_slot += 1;
        position->y = detail_y;
        group_data += 0xC;
        (*group_slot)->position->x = column_offset + 0x44;
        initial_index += 1;
        (*group_slot)->position->y = detail_y;
        group_slot += 1;
    } while (initial_index < 0x10);

    initial_index = 0;
    {
        ItemMenuPart **object_base;
        object_base = catalog_display_node_slots;
        entry_slot = (ItemMenuPart **)((object_index << 2) + (u8 *)object_base);
    }
    entry_data = catalog_grid_packets;
    do {
        column = initial_index >> 3;
        row = initial_index & 7;
        initial_index += 1;
        (*entry_slot)->handler = entry_data;
        entry_data += 0xC;
        (*entry_slot)->position->x = (column << 7) + 0x54;
        (*entry_slot)->position->y = row * 0x12 + 0x30;
        entry_slot += 1;
    } while (initial_index < 0x10);

    initial_index = 0;
    final_width = 0x10;
    final_x = 0xE0;
    {
        ItemMenuPart **object_base;
        object_base = catalog_display_node_slots;
        display_slot = &object_base[0x1C];
        object_base[0x61]->handler = D_80128614;
    }
    do {
        ((CatalogDisplayVector *)(*display_slot)->vector)->signed_halves.unk_06 = final_width;
        object = *display_slot;
        initial_index += 1;
        ((CatalogDisplayVector *)object->vector)->signed_halves.unk_08 = final_x;
        display_slot += 1;
    } while (initial_index < 0x46);
}
