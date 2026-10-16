#include "modules/dungeon_ovl_cb9000.h"

void func_8016DA38(S_80173A38_0 *arg0, void *arg1, CL_CB9000_80173A38_S_80173A38_1 *arg2, CL_CB9000_80173A38_S_80173A38_2 *arg3) {
    if (func_800AC82C(arg0,arg1,arg2,arg3) != 0) {
        if ((dungeonCheckActorFloorTrap(arg2, arg3) << 0x10) > 0) {
            arg0->CL_CB9000_80173A38_unk_8C = func_8016B02C;
        }
    } else if ((arg2->unk_2C == D_8016F2FC) && !(arg3->unk_1C & 0x208)) {
        arg2->unk_2C = D_8016F2AC;
        func_80047784(arg2, *((((s32) (gameWork.view.viewAngle + arg3->unk_2A + 0x100) >> 9) & 7) + D_8016F2AC), 0);
    }
}
