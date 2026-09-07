#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082660[];
extern M2C_UNK D_80097DE8;
extern M2C_UNK D_800D0178;


void func_800989C8(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80099754(arg1);
    func_80094984(&D_800D0178, arg0, arg2);
    arg0->unk_04.as_pm = &D_80097DE8;
    D_80082660[8] = 0;
    D_80082660[9] = 0;
}
