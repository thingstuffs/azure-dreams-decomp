#ifndef TOWN_MAP_POSITION_H
#define TOWN_MAP_POSITION_H
/* Prototypes of the functions defined in src/town/map/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_800A8BBC_0;
struct Vec4;

/* apply_building_tile_entry.c */
void apply_building_tile_entry(s16 x, s16 y, u8 entry_index);

/* copy_building_tiles_at_position.c */
void copy_building_tiles_at_position(s16 x, s16 y, u16 *src_tiles);

/* initialize_object_at_current_position.c */
void initialize_object_at_current_position(void);

/* process_raised_position_pair.c */
void process_raised_position_pair(s32 unused_arg, s32 *position);

/* query_offset_position_minus_x.c */
s16 query_offset_position_minus_x(struct Vec4 *vector, struct Vec4 *entries, s32 entry_index);

/* read_map_cell_at_tile_g01115.c */
s32 read_map_cell_at_tile(s32 tile_x, s32 tile_y);
s32 read_map_cell_at_world_position(s16 world_x, s16 world_y);
void write_wrapped_packed_nibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data);
void process_all_lookup_entries(s32 lookup_key, void *context);
void process_indexed_entry_record(s32 entry_index);
void upload_town_movie_pixel_data_2(void);
void advance_index_and_mark_completion(s32 *currentIndex);
void create_town_map_entry_processor(void);

/* write_square_position_offsets.c */
void write_square_position_offsets(s16 top_left, s16 top_right, s16 bottom_left, s16 bottom_right, struct S_800A8BBC_0 *pos);

#endif
