#include "common.h"
#include "m2c_compat.h"

void townCopyVariantBuildingTiles(s16 x, s16 y, u16 *src_tiles);                    /* extern */

/* Forwards tilemap coordinates to the tile copy routine. */
void townCopyBuildingTilesAtPosition(s16 x, s16 y, u16 *src_tiles) {
    townCopyVariantBuildingTiles(x, y, src_tiles);
}
