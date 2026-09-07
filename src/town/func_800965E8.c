#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80090C68;
extern M2C_UNK D_800D0078;


void func_80093D48(Rec_func_80094268_arg0 *arg0) {
    func_80094984(&D_800D0078, arg0);
    arg0->unk_00.as_pm = &D_80090C68;
    arg0->unk_0A.as_s16 = 0x54;
}
