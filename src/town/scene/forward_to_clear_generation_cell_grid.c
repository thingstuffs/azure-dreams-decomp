#include "common.h"

extern s32 clear_generation_cell_grid(void);
/* Returns the result of clear_generation_cell_grid with no arguments. */
s32 forward_to_clear_generation_cell_grid(void) { return clear_generation_cell_grid(); }
