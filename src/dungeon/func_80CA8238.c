#include "modules/dungeon_ovl_cc5000.h"

void func_80161A38(S_80173A38_0 *arg0, void *arg1, CL_CC5000_80173A38_S_80173A38_1 *arg2, CL_CC5000_80173A38_S_80173A38_2 *arg3) {
    if (update_actor_transform_from_parent(arg0,arg1,arg2,arg3) != 0) {
        if ((check_actor_floor_trap(arg2, arg3) << 0x10) > 0) {
            arg0->CL_CC5000_80173A38_unk_8C = func_8015F02C;
        }
    } else if ((arg2->unk_2C == D_801632FC) && !(arg3->unk_1C & 0x208)) {
        arg2->unk_2C = D_801632AC;
        func_80047784(arg2, *((((s32) (g_game_work.view.viewAngle + arg3->unk_2A + 0x100) >> 9) & 7) + D_801632AC), 0);
    }
}
