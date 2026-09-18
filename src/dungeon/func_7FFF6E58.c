#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800948DC();
M2C_UNK func_80094984();
extern M2C_UNK D_80092CD4;
extern M2C_UNK D_800D0140;

void func_800945B8(M2C_UNK **outputSlot, Rec_D_800E3D7C *state, M2C_UNK initContext) {
    func_800948DC();
    state->unk_14.as_s32 = 0xFFEF0000;
    func_80094984(&D_800D0140, outputSlot, initContext);
    *outputSlot = &D_80092CD4;
}
