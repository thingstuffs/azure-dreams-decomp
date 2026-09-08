#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

s32 func_800B68AC();                             /* extern */
M2C_UNK func_800B6E3C();                      /* extern */
extern M2C_UNK D_800B66E8;


void func_800B68C8(Rec_func_800B683C_arg0 *arg0, s32 arg1, s16 arg2) {
    arg0->unk_08 = arg2;
    arg0->unk_04 = arg1;
    arg0->unk_0C = 0;
    arg0->unk_0E = 0;
    arg0->unk_00 = &D_800B66E8;
    arg0->unk_14 = func_800B68AC(arg0->unk_08);
    func_800B6E3C(arg0);
}
