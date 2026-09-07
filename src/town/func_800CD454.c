#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

s32 func_8004A658();                /* extern */
M2C_UNK func_8008F104();     /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0678;


void func_800CABB4(s32 arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2) {
    arg2->unk_08 = func_8004A658(4, 1);
    func_8008F104(arg0, arg1, &D_800D0678);
    func_8009B218(arg0, arg1, arg2, 0);
}
