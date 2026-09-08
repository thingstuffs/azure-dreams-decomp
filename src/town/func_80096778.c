#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_80094C74();                     /* extern */
extern M2C_UNK D_80091260;
extern M2C_UNK D_800D0090;


void func_80093ED8(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    arg0->unk_3E.as_s16 = 6;
    func_80094C1C(arg0);
    func_80094C74(arg1);
    func_80094984(&D_800D0090, arg0, arg2);
    arg0->unk_00.as_pm = &D_80091260;
}
