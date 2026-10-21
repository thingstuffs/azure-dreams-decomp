#ifndef TOWN_MAP_MAP_CURSOR_INPUT_G00641_H
#define TOWN_MAP_MAP_CURSOR_INPUT_G00641_H
/* Map cursor input (G00641). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800BBAA4. */

#include "common.h"
#include "shared/runtime_dispatch.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern u8 town_map_selection_state[12];
extern void request_scene_state_with_parameters(s32 a0, s16 a1, s16 a2, s16 a3, s32 a4);
/* extern */
extern u8 D_800D185C;
extern u8 D_800D185D;

/* Functions defined in this translation unit. */
void store_state_and_update_tile_center(s32 state);
void update_wrapping_indices_and_input(void);

#endif
