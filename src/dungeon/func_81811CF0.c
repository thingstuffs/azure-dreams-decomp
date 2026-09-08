#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80026CF0_arg0.h"

extern M2C_UNK D_800789B8;


void func_80026CF0(Rec_func_80026CF0_arg0 *arg0, s32 arg1) {
    *arg0->unk_0C = &D_800789B8;
    *arg0->unk_10 = arg1;
}
