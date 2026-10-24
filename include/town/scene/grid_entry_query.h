#ifndef INCLUDE_TOWN_SCENE_GRID_ENTRY_QUERY_H
#define INCLUDE_TOWN_SCENE_GRID_ENTRY_QUERY_H

#include "common.h"

s32 find_entry_index_by_grid_bytes(s32 match_byte_1, s32 match_byte_0);
s32 is_result_valid(s32 grid_y, s32 grid_x);
s32 check_scene_query_result(s32 grid_y, s32 grid_x);
s32 has_matching_grid_entry(s32 grid_y, s32 grid_x);

#endif
