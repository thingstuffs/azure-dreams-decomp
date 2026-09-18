#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800948DC();
M2C_UNK func_80094984();
extern M2C_UNK D_8009204C;
extern M2C_UNK D_800D00B0;

void func_800942B0(Rec_func_80094268_arg0 *object, Rec_D_800E3D7C *state, M2C_UNK setupArg) {
    func_800948DC();
    state->unk_14.as_s32 = 0xFFEF0000;
    func_80094984(&D_800D00B0, object, setupArg);
    object->unk_00.as_pm = &D_8009204C;
    object->unk_0A.as_s16 = 0;
}
