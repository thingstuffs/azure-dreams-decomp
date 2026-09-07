#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_80091AF0;
extern M2C_UNK D_800D00E8;


void func_800940D0(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80053DA8(0x510);
    func_80094984(&D_800D00E8, arg0, arg2);
    arg0->unk_00.as_pm = &D_80091AF0;
    arg0->unk_0A.as_s16 = 0xC;
}
