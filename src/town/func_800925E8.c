#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"

M2C_UNK func_8008FCF4();                            /* extern */


void func_8008FD48(Rec_D_800FE490 *arg0, s32 arg1, s32 arg2) {
    func_8008FCF4();
    arg0->unk_08 = arg1;
    arg0->unk_0C = arg2;
    arg0->unk_15 = 1;
    arg0->unk_14 = 0;
}
