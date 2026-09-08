#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80026CF0_arg0.h"

M2C_UNK func_80026C00();         /* extern */
M2C_UNK func_80026D78();                       /* extern */


void func_80026E90(s8 *arg0, s32 arg1) {
    ((Rec_func_80026CF0_arg0 *)arg0)->unk_00 = arg1;
    func_80026C00(arg0 + 0x50, arg0 + 0x28, arg0 + 0x38);
    func_80026D78(arg0);
}
