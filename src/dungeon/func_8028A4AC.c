#include "modules/dungeon_floor_generate.h"

void func_8001D4AC(Rec_func_8001CE44_arg0 *region, s32 update_id) {
    u32 feature_roll;
    s16 saved_update_id = update_id;

    region->unk_0A = 1;
    feature_roll = func_800A6D30() & 0xFF;
    switch (feature_roll) {
    case 0:
        region->unk_0A = 2;
        return;
    case 1:
        if (((floor_generate_isolated_8028A4AC_S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
            break;
        }
        region->unk_0A = 3;
        D_8001F670 = 1;
        func_8001CFB8(region, saved_update_id);
        return;
    case 2:
        if (((floor_generate_isolated_8028A4AC_S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
            break;
        }
        D_8001F670 = 1;
        region->unk_0A = 2;
        func_8001D328(region, saved_update_id);
        return;
    case 4:
        if (((floor_generate_isolated_8028A4AC_S_8001D4AC_1 *)(&D_8001F670))->unk_00 != 0) {
            break;
        }
        D_8001F670 = 1;
        region->unk_0A = 4;
        func_8001D0F4(region, saved_update_id);
        return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        func_8001CEC0(region, saved_update_id);
    }
    return;
}
