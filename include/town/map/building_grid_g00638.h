#ifndef TOWN_MAP_BUILDING_GRID_G00638_H
#define TOWN_MAP_BUILDING_GRID_G00638_H
/* Building grid. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - town/func_800B9C24, town/func_800B9C70, town/func_800B9C90. */

#include "common.h"
#include "m2c_compat.h"

/* Image IDs used by the building grid exceed four; the full table bound is unknown. */
extern u16 *D_800D1868[];

void initialize_building_region_resources(void);

/* Functions defined in this translation unit. */
void clear_halfword_grid_128(s16 *grid);
void update_active_building_entries(void);
void clear_and_initialize_building_grid(void *grid);


void initialize_building_scene_objects(void *draw_param);

struct GameWork;
void no_op_building_callback(struct GameWork *work, s32 size, s32 limit);

#endif
