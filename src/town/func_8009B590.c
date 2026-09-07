#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098180;
extern M2C_UNK D_800D0090;


void func_80098CF0(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80099754(arg1);
    func_80094984(&D_800D0090, arg0, arg2);
    D_80082668 = 0;
    arg0->unk_04.as_pm = &D_80098180;
    arg0->unk_0A.as_s16 = 0x10;
    arg0->unk_10.as_s16 = 0x400;
}
