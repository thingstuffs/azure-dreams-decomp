#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800CB73C(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_800CBB68();                /* extern */


void func_800CB7EC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800CB73C(arg0);
        func_800CBB68(arg0->unk_96.as_s8, arg0->unk_88, arg0->unk_8A);
        func_800C4174(arg0, arg1, arg2);
    }
}
