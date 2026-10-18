#include "modules/dungeon_ovl_ccb000.h"

void func_8015BA38(S_80173A38_0 *arg0, void *arg1, CL_CCB000_80173A38_S_80173A38_1 *arg2, CL_CCB000_80173A38_S_80173A38_2 *arg3) {
    if (update_actor_transform_from_parent(arg0,arg1,arg2,arg3) != 0) {
        if ((check_actor_floor_trap(arg2, arg3) << 0x10) > 0) {
            arg0->CL_CCB000_80173A38_unk_8C = func_8015902C;
        }
    } else if ((arg2->unk_2C == D_8015D2FC) && !(arg3->unk_1C & 0x208)) {
        arg2->unk_2C = D_8015D2AC;
        func_80047784(arg2, *((((s32) (g_game_work.view.viewAngle + arg3->unk_2A + 0x100) >> 9) & 7) + D_8015D2AC), 0);
    }
}
