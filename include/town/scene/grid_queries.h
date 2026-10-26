#ifndef INCLUDE_TOWN_SCENE_GRID_QUERIES_H
#define INCLUDE_TOWN_SCENE_GRID_QUERIES_H

#include "common.h"

s32 has_grid_entry(s32 grid_y, s32 grid_x);
s32 has_grid_entry_b(s32 grid_y, s32 grid_x);
s32 has_grid_entry_c(s32 grid_y, s32 grid_x);
s32 has_grid_entry_d(s32 grid_y, s32 grid_x);
s32 has_grid_entry_e(s32 grid_y, s32 grid_x);

u32 apply_rectangle_preset_10x7(void);
u32 apply_target_grid_rectangle(s32 target_x, s32 target_y);
s32 forward_context_request_to_handler_d(void *context, s32 request);

#endif
