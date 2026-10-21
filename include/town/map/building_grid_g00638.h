#ifndef TOWN_MAP_BUILDING_GRID_G00638_H
#define TOWN_MAP_BUILDING_GRID_G00638_H
/* Building grid (G00638). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9C24, CL:town/func_800B9C70, CL:town/func_800B9C90. */

#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_building_region_resources(void);

/* Functions defined in this translation unit. */
void clear_halfword_grid_128(s16 *grid);
void update_active_building_entries(void);
void clear_and_initialize_building_grid(s32 grid);

#endif
