#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800920BC();                            /* extern */
M2C_UNK func_8009431C();        /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80096810();                      /* extern */
extern u8 D_800CFCEE;


void func_8009204C(s32 arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    func_80096810(arg1);
    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);
    if (D_800CFCEE != 0) {
        arg1->unk_14.as_s32 = 0;
        func_800954F4(arg1);
        func_800920BC();
        return;
    }
    func_80095388(arg1);
    if (arg1->unk_14.as_s32 >= 0) {
        func_8009431C(arg0, arg1, arg2);
    }
}
