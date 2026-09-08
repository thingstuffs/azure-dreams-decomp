#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"



extern M2C_UNK func_80038A00;

s32 func_80034FE4(Rec_D_80082A38 *arg0) {
    return arg0->unk_9C != (s32) &func_80038A00;
}
