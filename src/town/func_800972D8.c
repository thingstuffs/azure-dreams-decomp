#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

M2C_UNK func_800949C4();                         /* extern */


void func_80094A38(s32 arg0, Rec_D_80082D58 *arg1) {
    arg1->unk_1C = arg0;
    func_800949C4(arg0, arg1->unk_10);
}
