#ifndef TOWN_MAP_POSITION_READ_MAP_CELL_AT_TILE_G01115_H
#define TOWN_MAP_POSITION_READ_MAP_CELL_AT_TILE_G01115_H
/* read map cell at tile g01115. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01115 - CL:town/func_8008E9D4, CL:town/func_8008EA64, CL:town/func_8008EAB4, CL:town/func_8008EB2C, PD:town/engine:800CFCA8, PD:town/engine:800FC428. */

/* cfail-repair: unary-star-typing; preserve the warm source shape */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "town/map/range_group_checks_g00652.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

typedef struct S_8008C134_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
} S_8008C134_0;

typedef struct S_8008EC14_node {
    u8 pad0[0x10];
    void *field_0x10;
    u8 pad14[0x20 - 0x14];
    s32 field_0x20;
} S_8008EC14_node;

/* extern */
extern u8 D_800FC428;
void upload_pixel_rectangle(s16, s16, s16, s16, const void *);
/* extern */
extern s32 map_scene_selector_alias;
extern void *town_map_processor[];
extern s32 D_8008C304[];

/* Functions defined in this translation unit. */
s32 read_map_cell_at_tile(s32 tile_x, s32 tile_y);
s32 read_map_cell_at_world_position(s16 world_x, s16 world_y);
void write_wrapped_packed_nibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data);
void process_all_lookup_entries(s32 lookup_key, void *context);
void process_indexed_entry_record(s32 entry_index);
void upload_town_movie_pixel_data_2(void);
void advance_index_and_mark_completion(s32 *currentIndex);
void create_town_map_entry_processor(void);

#endif
