#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800941D8();    /* extern */
M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80095C80();                     /* extern */
extern M2C_UNK D_800D00E0;


void func_80091CE0(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v0;

    func_80095C80(arg1);
    if (arg0->unk_0A.as_s16 == 0) {
        func_80094984(&D_800D00E0, arg0, arg2);
    }
    temp_v0 = (u16) arg0->unk_0A.as_s16 - 1;
    arg0->unk_0A.as_s16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800941D8(arg0, arg1, arg2);
    }
}
