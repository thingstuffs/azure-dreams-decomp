#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800C30E0();                                /* extern */
M2C_UNK func_800C382C();    /* extern */


void func_800C34EC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    if (func_800C30E0() == 0) {
        temp_v0 = arg0->unk_6C.as_u16 - 1;
        arg0->unk_6C.as_u16 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            func_800C382C(arg0, arg1, arg2);
        }
    }
}
