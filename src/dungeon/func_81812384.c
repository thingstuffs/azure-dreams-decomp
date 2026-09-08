#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027328_arg0.h"

s32 func_80026E30();                             /* extern */
s32 func_80027008();               /* extern */
M2C_UNK func_8004B1A4();                         /* extern */


void *func_80027384(Rec_func_80027328_arg0 *arg0, M2C_UNK arg1) {
    s32 temp_v0;

    func_8004B1A4(arg0->unk_08);
    temp_v0 = func_80026E30(arg0->unk_00);
    arg0->unk_04 = temp_v0;
    arg0->unk_08 = func_80027008(arg0->unk_00, arg1, temp_v0);
    return arg0;
}
