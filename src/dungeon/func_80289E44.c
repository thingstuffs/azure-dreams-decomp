#include "modules/dungeon_floor_generate.h"

void update_region_until_complete(Rec_func_8001CE44_arg0 *region, s16 update_id) {
    do {
        fill_region_with_random_patches(region, update_id);
        choose_random_region_feature(region, update_id);
    } while ((mark_path_through_neighboring_tiles(update_id) << 0x10) == 0);
    mask_generation_cell_rect(region->unk_00, region->unk_02, region->unk_04, region->unk_06, 0xF);
}
