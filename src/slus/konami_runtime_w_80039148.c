#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"



extern M2C_UNK func_800381A4;
extern M2C_UNK func_800387D0;

void func_80039148(Rec_func_800381D0_arg0 *arg0) {
    M2C_UNK *var_v0;

    arg0->unk_20 = 0;
    if (arg0->unk_22 < (arg0->unk_25 - 1)) {
        arg0->unk_22 = (s16) ((u16) arg0->unk_22 + 1);
        if (arg0->unk_2E == 1) {
            var_v0 = &func_800381A4;
            arg0->unk_18 = 0;
            goto block_4;
        }
    } else {
        var_v0 = &func_800387D0;
block_4:
        arg0->unk_10 = var_v0;
    }
}
