#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027328_arg0.h"

s32 func_80025080();                             /* extern */
s32 func_80026DE0();                    /* extern */
M2C_UNK func_8004B1A4();                         /* extern */


void *func_80027328(Rec_func_80027328_arg0 *arg0, M2C_UNK arg1) {
    func_8004B1A4(arg0->unk_08);
    arg0->unk_04 = func_80025080(arg0->unk_00);
    arg0->unk_08 = func_80026DE0(arg0->unk_00, arg1);
    return arg0;
}
