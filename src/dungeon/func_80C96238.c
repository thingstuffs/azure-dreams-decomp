#include "modules/dungeon_ovl_cb3000.h"

void func_80173A38(S_80173A38_0 *arg0, void *arg1, CB_80173A38_S_80173A38_1 *arg2, CB_80173A38_S_80173A38_2 *arg3) {
    if (update_actor_transform_from_parent(arg0,arg1,arg2,arg3) != 0) {
        if ((check_actor_floor_trap(arg2, arg3) << 0x10) > 0) {
            arg0->CB_80173A38_unk_8C = func_8017102C;
        }
    } else if ((arg2->unk_2C == D_801752FC) && !(arg3->unk_1C & 0x208)) {
        arg2->unk_2C = D_801752AC;
        select_sprite_entry(arg2, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + arg3->unk_2A + 0x100) >> 9) & 7) + D_801752AC), 0);
    }
}
