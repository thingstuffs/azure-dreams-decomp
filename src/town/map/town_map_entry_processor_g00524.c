/* Town map entry processor (G00524).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8008E9D4, CL:town/func_8008EA64, CL:town/func_8008EAB4, CL:town/func_8008EB2C, PD:town/engine:800CFCA8, PD:town/engine:800FC428.
 */
#include "town/map/town_map_entry_processor_g00524.h"

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

/* Call upload_town_movie_pixel_data with fixed parameters when D_8006ADD4 equals 0x13000C. */
void upload_town_movie_pixel_data_2(void) {
    if (map_scene_selector_alias == 0x13000C) {
        upload_town_movie_pixel_data(0x360, 0x100, 0x20, 0x80, &D_800FC428);
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
        object_flag_block.flags |= 0x8000;
    }
}

/* Initialize an allocated node and store its data pointer in D_800CFCA8. */
void create_town_map_entry_processor(void)
{
    S_8008EC14_node *node = func_8003FC64(0);

    if (node != 0) {
        node->field_0x10 = D_8008C304;
        node->field_0x20 = 0;
        node = (S_8008EC14_node *)((u8 *)node + 0x20);
        town_map_processor[0] = node;
    }
}
