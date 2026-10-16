#include "common.h"

extern s32 townCopyVariantBuildingTiles(s16 x, s16 y, u16 *src_tiles);
extern s32 D_800D17D8[];

/* Apply the selected table entry at the given coordinates. */
void townApplyBuildingTileEntry(s16 x, s16 y, u8 entry_index) {
    townCopyVariantBuildingTiles(x, y, D_800D17D8[entry_index]);
}
