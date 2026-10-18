#include "common.h"
#include "m2c_compat.h"

void copy_variant_building_tiles(s16 x, s16 y, u16 *src_tiles);                    /* extern */

/* Forwards tilemap coordinates to the tile copy routine. */
void copy_building_tiles_at_position(s16 x, s16 y, u16 *src_tiles) {
    copy_variant_building_tiles(x, y, src_tiles);
}
