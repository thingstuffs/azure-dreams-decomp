#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_8009A1A4();        /* extern */


void func_80099B00(s32 arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    arg1->unk_08.at00_s32.v = (s32) (arg1->unk_08.at00_s32.v + arg1->unk_14.as_s32);
    func_80095388(arg1);
    if (arg1->unk_14.as_s32 >= 0) {
        func_8009A1A4(arg0, arg1, arg2);
    }
}
