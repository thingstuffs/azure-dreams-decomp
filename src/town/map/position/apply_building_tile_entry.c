#include "common.h"
#include "town/map.h"
#include "town/map/position.h"

extern u16 *D_800D17D8[];

/* Apply the selected table entry at the given coordinates. */
void apply_building_tile_entry(s16 x, s16 y, u8 entry_index) {
    copy_variant_building_tiles(x, y, D_800D17D8[entry_index]);
}
