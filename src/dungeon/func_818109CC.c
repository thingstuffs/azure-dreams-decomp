#include "modules/dungeon_ovl_1830850.h"

s32 func_800259CC(Rec_func_80025850_arg0 *context) {
    s32 check_passed;

    check_passed = 0;
    if (context->unk_08 == 4) {
        check_passed = func_80026C20(((ovl_1830850_818109CC_S_800259CC_2 *)(((Rec_func_80025850_arg0 *)context)->unk_18))->unk_28) == 0;
    }
    return check_passed;
}
