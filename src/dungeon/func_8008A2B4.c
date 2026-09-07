#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

M2C_UNK func_8009F644(); /* extern */
M2C_UNK func_800A56E0();                     /* extern */


void func_8008FA14(Rec_func_8008ACDC_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    arg0->unk_9A.as_s8 = 0x20;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C.as_s32 = 0;
    func_800A56E0(0x512);
    arg0->unk_A2 = (u16) (arg0->unk_A2 & 0xFFEF);
    func_8009F644(arg3, 0x30, arg0->unk_96.as_s16, 0);
}
