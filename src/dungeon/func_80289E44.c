#include "modules/dungeon_floor_generate.h"

void dungeonUpdateRegionUntilComplete(Rec_func_8001CE44_arg0 *region, s16 update_id) {
    do {
        dungeonFillRegionWithRandomPatches(region, update_id);
        dungeonChooseRandomRegionFeature(region, update_id);
    } while ((dungeonMarkPathThroughNeighboringTiles(update_id) << 0x10) == 0);
    dungeonMaskGenerationCellRect(region->unk_00, region->unk_02, region->unk_04, region->unk_06, 0xF);
}
