/* Relink of matched dungeon/func_80289E44; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

void func_8001CE44(Rec_func_8001CE44_arg0 *region, s16 update_id) {
    do {
        func_8001D5D8(region, update_id);
        func_8001D4AC(region, update_id);
    } while ((func_80017BEC(update_id) << 0x10) == 0);
    func_80017480(region->unk_00, region->unk_02, region->unk_04, region->unk_06, 0xF);
}
