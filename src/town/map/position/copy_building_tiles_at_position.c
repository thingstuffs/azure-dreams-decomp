#include "common.h"
#include "m2c_compat.h"
#include "town/map.h"
#include "town/map/position.h"

/* Forwards tilemap coordinates to the tile copy routine. */
void copy_building_tiles_at_position(s16 x, s16 y, u16 *src_tiles) {
    copy_variant_building_tiles(x, y, src_tiles);
}
