#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

s32 func_8008EFA0();                                /* extern */


void func_8008F01C(Rec_D_800CFCB4 *arg0, s32 arg1, s32 arg2) {
    if (func_8008EFA0() != 0) {
        arg0->unk_08 = arg1;
        arg0->unk_0C = arg2;
        arg0->unk_15 = 1;
        arg0->unk_14 = 0;
    }
}
