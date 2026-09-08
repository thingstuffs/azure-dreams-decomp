#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027328_arg0.h"

s32 func_80026E70();                    /* extern */
s32 func_8002714C();      /* extern */
M2C_UNK func_8004B1A4();                         /* extern */


void *func_800273E4(Rec_func_80027328_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_a2;

    func_8004B1A4(arg0->unk_08);
    temp_a2 = func_80026E70(arg0->unk_00, arg2) + 5;
    arg0->unk_04 = temp_a2;
    arg0->unk_08 = func_8002714C(arg0->unk_00, arg1, temp_a2, arg2);
    return arg0;
}
