/* Copies nonzero cells from a size-prefixed block into the shared map grid. */
#include "common.h"
#include "town/map.h"

extern u16 town_tile_grid[];

/* Returns the current value of town_tile_grid. */
static __inline__ u16 *grid_base(void) { return town_tile_grid; }

/* Copies a width-and-height-prefixed block to the destination grid, skipping zero entries. */
void blit_nonzero_u16_block_to_grid(s16 dst_x, s16 dst_y, u16 *src) {
    s16 next_row;
    s16 next_col;
    s16 row;
    s16 col;
    u16 height;
    u16 width;
    u16 entry;

    width = *src++;
    height = *src++;
    row = 0;
    while ((row << 0x10) < (height << 0x10)) {
        col = 0;
        while (col < (s16) width) {
            entry = *src;
            if (entry != 0) {
                grid_base()[(((row + dst_y) << 7) + col + dst_x)] = entry;
            }
            next_col = col + 1;
            col = next_col;
            src++;
        }
        next_row = row + 1;
        row = next_row;
    }
}
