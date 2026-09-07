#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();
M2C_UNK func_80094C1C();
extern M2C_UNK D_80092320;
extern M2C_UNK D_800D0108;


void func_800943B8(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    func_80094C1C(arg0, arg1, arg2, arg3);
    func_80094984(&D_800D0108, arg0, arg2);
    arg0->unk_00.as_pm = &D_80092320;
    arg0->unk_0A.as_s16 = 6;
}
