/* Set scaled record coordinates.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00704 - XB:town/func_8032FE28.
 */
#include "town/scene/set_scaled_record_coordinates_g00704.h"
#include "town/scene.h"

/* Store coordinates scaled by 64 and offset by 0x220. */
void set_scaled_record_coordinates(s32 unused, s32 x, s32 y) {
    u8 *base = *(u8 **)((u8 *)&town_scene_root);

    *(s32 *)(*(u8 **)(base + 0x1C) + 4) = (x << 6) + 0x220;
    *(s32 *)(*(u8 **)(base + 0x1C) + 8) = (y << 6) + 0x220;
}

/* Stores (value + 1) * 16 through the global object's pointer at offset 0x1C. */
void set_scaled_pointer_value(s32 value)
{
    s32 *value_ptr = *(s32 **)((u8 *)(&town_scene_root));
    value_ptr = *(s32 **)((u8 *)value_ptr + 0x1C);
    *value_ptr = (value + 1) * 0x10;
}

/* Set the position from coordinates scaled by 64 and the selected entry offsets. */
void set_position_from_tile_and_entry_offsets(s32 unused, u32 x, u32 y)
{
    void *root = town_scene_root;
    S_8001A678_1 *entry_table;
    TownPositionState *position;
    u32 entry_address;
    s32 x_offset;
    s32 y_offset;

    entry_table = ((Rec_D_80016000 *)root)->unk_30;
    entry_address = ((u32)((Rec_D_80016000 *)root)->entry_index);
    {
        entry_address <<= 5;
    }
    {
        entry_table = entry_table->unk_00;
    }
    entry_address += (u32)entry_table;
    position = ((Rec_D_80016000 *)root)->position;
    {
        x <<= 6;
    }
    x_offset = ((S_8001A678_2 *)((void *)entry_address))->unk_0C;
    x_offset += 0x20;
    x += x_offset;
    position->x = x;
    root = ((Rec_D_80016000 *)root)->position;
    {
        y <<= 6;
    }
    y_offset = ((S_8001A678_2 *)((void *)entry_address))->unk_0E;
    y_offset += 0x20;
    y += y_offset;
    ((TownPositionState *)root)->y = y;
}

/* Stores two values scaled by 32 in the current record's auxiliary data. */
void set_record_scaled_auxiliary_values(s32 unused, s32 value_04, s32 value_08) {
    town_scene_root->position->x = (s32) (value_04 << 5);
    town_scene_root->position->y = (s32) (value_08 << 5);
}

/* Set position coordinates to the selected entry's offsets plus scaled x and y. */
void set_selected_entry_position(s32 unused, s32 x, s32 y)
{
    u8 *root = town_scene_root;
    void *entry_ptr;
    void *position;
    s32 index;
    s16 value;

    entry_ptr = (*(void **)((u8 *)root + 0x30));
    index = (*(s32 *)((u8 *)root + 8));
    index <<= 5;
    entry_ptr = (*(void **)((u8 *)entry_ptr + 0));
    index += (s32)entry_ptr;
    position = (*(void **)((u8 *)root + 0x1C));
    x <<= 5;
    value = ((S_8001A704_0 *)((void *)index))->unk_0C;
    x += value;
    ((S_8001A704_1 *)position)->unk_04 = x;
    {
        TownDestinationYView *position2;

        position2 = (*(void **)((u8 *)root + 0x1C));
        y <<= 5;
        value = ((S_8001A704_0 *)((void *)index))->unk_0E;
        y += value;
        position2->unk_08 = y;
    }
}

/* Set destination coordinates from the tile center and scaled offsets. */
void set_tile_center_destination(s32 unused, s32 x_offset, s32 y_offset) {
    S_8001A760_0 *ctx;
    S_8001A760_1 *tile;
    S_8001A760_2 *x_dest;
    TownDestinationYView *y_dest;
    s32 tile_coord;
    s32 tile_coord_2;

    ctx = *(void **)((u8 *)&town_scene_root);
    tile = (u8 *)*ctx->unk_30 + (ctx->unk_08 << 5);
    x_dest = ctx->unk_1C;
    x_offset = (x_offset << 6) / 10;
    tile_coord_2 = tile->unk_0C;
    tile_coord_2 += 0x20;
    x_dest->unk_04 = x_offset + tile_coord_2;

    y_dest = ctx->unk_1C;
    y_offset = (y_offset << 6) / 10;
    tile_coord = tile->unk_0E;
    tile_coord += 0x20;
    y_dest->unk_08 = y_offset + tile_coord;
}

/* Scale and offset the two coordinates stored in the global destination. */
void set_scaled_destination_coordinates(s32 unused, s32 x, s32 y)
{
    void *base;

    (void)unused;
    base = *(void **)((s8 *)(&town_scene_root));
    ((S_8001A7F4_1 *)((S_8001A7F4_0 *)base)->unk_1C)->unk_04 = (x << 6) / 10 + 0x220;
    ((S_8001A7F4_0 *)((S_8001A7F4_0 *)base)->unk_1C)->unk_08 = (y << 6) / 10 + 0x220;
}
