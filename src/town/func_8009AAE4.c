#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_800982D0();                            /* extern */
M2C_UNK func_80098928();        /* extern */


void func_80098244(s32 arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    s16 temp_v0_2;
    u16 temp_v1;

    temp_v1 = (u16) arg1->unk_00.at02_s16.v;
    if (arg1->unk_00.at02_s16.v < 0x4C2) {
        temp_v0 = temp_v1 + 4;
        arg1->unk_00.at02_s16.v = temp_v0;
        if (temp_v0 < 0x4C2) {
            func_800982D0();
            return;
        }
        goto block_5;
    }
    temp_v0_2 = temp_v1 - 4;
    arg1->unk_00.at02_s16.v = temp_v0_2;
    if (temp_v0_2 < 0x4C3) {
block_5:
        arg1->unk_00.at02_s16.v = 0x4C2;
        func_80033AA8(0x12);
        func_80098928(arg0, arg1, arg2);
    }
}
