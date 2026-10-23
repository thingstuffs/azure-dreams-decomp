/* Read map cell at tile g01115.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01115 - CL:town/func_8008E9D4, CL:town/func_8008EA64, CL:town/func_8008EAB4, CL:town/func_8008EB2C, PD:town/engine:800CFCA8, PD:town/engine:800FC428.
 */
#include "town/map/position/read_map_cell_at_tile_g01115.h"
#include "shared/object_flags.h"

/* Read the low 14 bits of the map entry at masked tile coordinates. */
s32 read_map_cell_at_tile(s32 tile_x, s32 tile_y) {
    GameWork *map_state;
    u8 *map_layout;

    map_state = &g_game_work;
    map_layout = (u8 *)map_state + 0x1DC;
    return *(u16 *)(((s32) (((((S_8008C134_0 *)map_layout)->unk_18 & tile_x)
        + ((s16) (((S_8008C134_0 *)map_layout)->unk_1A & tile_y) << ((S_8008C134_0 *)map_layout)->unk_14)) << 0x10)
        >> 0xF) + ((s32)map_state->map.cells)) & 0x3FFF;
}

/* Read the map entry value at world coordinates converted to tiles. */
s32 read_map_cell_at_world_position(s16 world_x, s16 world_y) {
    return read_map_cell_at_tile(world_x / 0x40, world_y / 0x40) & 0xFFFF;
}

/* Write a nibble into packed data at a wrapped index. */
void write_wrapped_packed_nibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data)
{
    s32 wrapped_index;
    s32 packed_byte;

    wrapped_index = index % nibble_count;
    nibble &= 0xF;
    packed_data += wrapped_index / 2;

    if (!(wrapped_index & 1)) {
        packed_byte = (*packed_data & 0xF0) | nibble;
    } else {
        packed_byte = (*packed_data & 0xF) | (nibble << 4);
    }

    *packed_data = packed_byte;
}

/* Converts and processes all 128 entries for the given lookup key. */
void process_all_lookup_entries(s32 lookup_key, void *context) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 0x80; entry_index++) {
        write_wrapped_packed_nibble(pass_value_and_range_groups(read_map_cell_at_tile((s16)entry_index, (s16)lookup_key) & 0xFFFF), entry_index, 0x80, context);
    }
}

/* Pass the entry index and its 64-byte record to process_all_lookup_entries. */
void process_indexed_entry_record(s32 entry_index) {
    process_all_lookup_entries(entry_index, (entry_index << 6) + &D_800FC428);
}

/*
 * Uploads the 32-by-128 pixel block at D_800FC428 to VRAM (0x360, 0x100) only for scene selector
 * 0x13000C.
 */
void upload_town_movie_pixel_data_2(void) {
    if (map_scene_selector_alias == 0x13000C) {
        upload_pixel_rectangle(0x360, 0x100, 0x20, 0x80, &D_800FC428);
    }
}

/* Processes the current index, advances it, and marks completion at 128. */
void advance_index_and_mark_completion(s32 *currentIndex)
{
    s32 nextIndex;

    process_indexed_entry_record(*currentIndex);
    nextIndex = *currentIndex + 1;
    *currentIndex = nextIndex;
    if (nextIndex >= 0x80) {
        *(u16 *)((u8 *)currentIndex - 2) |= 0x8000;
        town_map_processor[0] = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/*
 * Allocates an object node, selects D_8008C304 as its handler, and saves its cleared data area in
 * town_map_processor.
 */
void create_town_map_entry_processor(void)
{
    S_8008EC14_node *node = allocate_flagged_object_node(0);

    if (node != 0) {
        node->field_0x10 = D_8008C304;
        node->field_0x20 = 0;
        node = (S_8008EC14_node *)((u8 *)node + 0x20);
        town_map_processor[0] = node;
    }
}
