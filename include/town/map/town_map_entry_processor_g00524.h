#ifndef TOWN_MAP_TOWN_MAP_ENTRY_PROCESSOR_G00524_H
#define TOWN_MAP_TOWN_MAP_ENTRY_PROCESSOR_G00524_H
/* Town map entry processor shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8008E9D4, CL:town/func_8008EA64, CL:town/func_8008EAB4, CL:town/func_8008EB2C, PD:town/engine:800CFCA8, PD:town/engine:800FC428. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

typedef struct S_8008EC14_node {
    u8 pad0[0x10];
    void *field_0x10;
    u8 pad14[0x20 - 0x14];
    s32 field_0x20;
} S_8008EC14_node;

extern s32 read_map_cell_at_tile(s32 tile_x, s32 tile_y);
extern s32 pass_value_and_range_groups(s32 value);
/* extern */
extern u8 D_800FC428;
void upload_town_movie_pixel_data(s16, s16, s16, s16, const void *);
/* extern */
extern s32 D_8006ADD4;
extern void *D_800CFCA8[];
extern s32 D_8008C304[];

/* Functions defined in this translation unit. */
void write_wrapped_packed_nibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data);
void process_all_lookup_entries(s32 lookup_key, void *context);
void process_indexed_entry_record(s32 entry_index);
void upload_town_movie_pixel_data_2(void);
void advance_index_and_mark_completion(s32 *currentIndex);
void create_town_map_entry_processor(void);

#endif
