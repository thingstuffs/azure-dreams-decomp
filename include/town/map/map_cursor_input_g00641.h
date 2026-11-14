#ifndef TOWN_MAP_MAP_CURSOR_INPUT_G00641_H
#define TOWN_MAP_MAP_CURSOR_INPUT_G00641_H
/* Map cursor input. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800BBAA4. */

#include "common.h"
#include "shared/runtime_dispatch.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern u8 town_map_selection_state[12];
/* extern */
extern u8 D_800D185C;
extern u8 D_800D185D;

/* Functions defined in this translation unit. */
void select_building_and_request_scene(s32 state);
void update_map_cursor_from_input(void);

#endif
