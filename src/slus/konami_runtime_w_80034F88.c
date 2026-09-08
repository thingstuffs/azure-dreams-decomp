#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"



void func_80034F88(void *arg0, s32 arg1) {
    ((Rec_D_80082A38 *)arg0)->unk_34 = arg1;
    ((Rec_D_80082A38 *)arg0)->unk_38 = arg1;
    ((Rec_D_80082A38 *)arg0)->unk_108 = (s32) (arg0 + 0xC8);
}
