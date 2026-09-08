#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_80090200(); /* extern */



/* extern */

void func_800B69DC(Rec_func_8008ACDC_arg0 *arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    s16 temp_v1;

    temp_v1 = arg3->unk_64.as_s16;
    if ((temp_v1 < 0) || (arg0->unk_10C & 1)) {
        arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v & 0xF7FF);
        func_8008CAA0(arg0, arg1, arg2, arg3);
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if ((arg0->unk_9A.as_u8 != 0xD) && (arg3->unk_1C.as_s32 & 0x200)) {
        arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v & 0xF7FF);
        func_80090200(arg0, arg1, arg2, arg3);
    }
}
