#include "modules/dungeon_ovl_cd7000.h"

void func_8014FA38(S_80173A38_0 *arg0, void *arg1, CL_CD7000_80173A38_S_80173A38_1 *arg2, CL_CD7000_80173A38_S_80173A38_2 *arg3) {
    if (func_800AC82C(arg0,arg1,arg2,arg3) != 0) {
        if ((dungeonCheckActorFloorTrap(arg2, arg3) << 0x10) > 0) {
            arg0->CL_CD7000_80173A38_unk_8C = func_8014D02C;
        }
    } else if ((arg2->unk_2C == D_801512FC) && !(arg3->unk_1C & 0x208)) {
        arg2->unk_2C = D_801512AC;
        func_80047784(arg2, *((((s32) (gameWork.view.viewAngle + arg3->unk_2A + 0x100) >> 9) & 7) + D_801512AC), 0);
    }
}
