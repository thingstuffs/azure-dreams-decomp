#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern M2C_UNK func_80094A60();


void func_80094984(s32 *arg0, Rec_func_80094268_arg0 *arg1) {
    if (arg0[arg1->unk_16] != 0) {
        func_80094A60();
    }
}
