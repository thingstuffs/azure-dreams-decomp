#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80025850_arg0.h"


typedef struct S_800259CC_2 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800259CC_2;   /* ((Rec_func_80025850_arg0 *)arg0)->unk_18 in func_800259CC */




s32 func_80026C20();                    /* extern */


s32 func_800259CC(Rec_func_80025850_arg0 *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if (arg0->unk_08 == 4) {
        var_a1 = func_80026C20(((S_800259CC_2 *)(((Rec_func_80025850_arg0 *)arg0)->unk_18))->unk_28, 0) == 0;
    }
    return var_a1;
}
