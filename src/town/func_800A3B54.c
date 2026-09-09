#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80100B70.h"

M2C_UNK func_800A17CC(Rec_D_80100B70 *, s32);                            /* extern */


void func_800A12B4(Rec_D_80100B70 *arg0, s32 arg1) {
    u16 temp_v0;

    temp_v0 = arg0->unk_12 - 4;
    arg0->unk_12 = temp_v0;
    if ((s16) temp_v0 < 4) {
        arg0->unk_12 = 4U;
    }
    arg0->unk_6E = (u16) ((arg0->unk_6E + 1) & 0x7F);
    func_800A17CC(arg0, arg1);
}
