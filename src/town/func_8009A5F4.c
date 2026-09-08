#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80097D54_arg0.h"

s32 func_800352FC();                                /* extern */
M2C_UNK func_80093D90();    /* extern */
M2C_UNK func_80098988();    /* extern */
extern M2C_UNK D_800CFFF0;



void func_80097D54(Rec_func_80097D54_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    if (func_800352FC() == 0) {
        temp_v0 = arg0->unk_0A - 1;
        arg0->unk_0A = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            if (arg0->unk_1C == &D_800CFFF0) {
                func_80093D90(arg0, arg1, arg2);
                return;
            }
            goto block_6;
        }
    } else {
block_6:
        func_80098988(arg0, arg1, arg2);
    }
}
