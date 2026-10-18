#include "common.h"

extern s32 read_map_cell_at_tile(s16 tile_x, s16 tile_y);
extern s32 pass_value_and_range_groups(s32 value);
extern void write_wrapped_packed_nibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data);

/* Converts and processes all 128 entries for the given lookup key. */
void process_all_lookup_entries(s16 lookup_key, void *context) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 0x80; entry_index++) {
        write_wrapped_packed_nibble(pass_value_and_range_groups(read_map_cell_at_tile(entry_index, lookup_key) & 0xFFFF), entry_index, 0x80, context);
    }
}
