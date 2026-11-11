#ifndef TOWN_MAP_FLAGGED_TILE_SCAN_G00593_H
#define TOWN_MAP_FLAGGED_TILE_SCAN_G00593_H
/* Flagged tile scan shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AE700, CL:town/func_800AE78C, CL:town/func_800AEA50, CL:town/func_800AEC1C. */

#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"

typedef struct {
    u8 a;
    u8 b;
    u8 pad2;
    u8 pad3;
} S_80081508;

typedef struct {
    s32 map_base;
    u8 pad04[0x10];
    s16 x_shift;
    s16 y_shift;
} GridInfo;

typedef struct {
    u8 *field0;
    u8 unk04[0x10];
    s16 field14;
    s16 field16;
} Config;

extern s32 has_runtime_key_pair(s32, s32);
/* One 24-byte access prefix of the 32-byte GameWork.map subobject.
 * This alias has no repeated GridInfo records. */
extern GridInfo scene_geometry;

extern s16 tile_key_pair_count[5];
extern S_80081508 *tile_coordinate_records[3];

/* Functions defined in this translation unit. */
void append_valid_key_pair(s32 first_value, s32 second_value, u32 unused_cell);
s32 count_flagged_cells_in_opposite_directions(s32 dir, s16 start_x, s16 start_y);
s32 count_flagged_tiles_along_direction(s16 direction, s16 start_x, s16 start_y);
void clear_flagged_cells_and_reset_list(void);
void refresh_state_and_dispatch_angles(void);

#endif
