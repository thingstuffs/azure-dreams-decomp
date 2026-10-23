/* Building grid (G00638). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9C24, CL:town/func_800B9C70, CL:town/func_800B9C90. */
#include "town/map/building_grid_g00638.h"

/* Writes zero to all 16,384 consecutive halfwords in row-major order. */
void clear_halfword_grid_128(s16 *grid) {
    s16 *cell;
    s16 next_row;
    s16 next_column;
    s16 row;
    s16 column;

    cell = grid;
    row = 0;
    do {
        column = 0;
        do {
            *cell = 0;
            next_column = column + 1;
            column = next_column;
            cell += 1;
        } while (next_column < 0x80);
        next_row = row + 1;
        row = next_row;
    } while (next_row < 0x80);
}

/* Updates the active entries through initialize_building_region_resources. */
void update_active_building_entries(void) {
    initialize_building_region_resources();
}

/* Clears the 128-halfword grid and initializes its building scene objects. */
void clear_and_initialize_building_grid(s32 grid) {
    clear_halfword_grid_128(grid);
    initialize_building_scene_objects(grid);
}
