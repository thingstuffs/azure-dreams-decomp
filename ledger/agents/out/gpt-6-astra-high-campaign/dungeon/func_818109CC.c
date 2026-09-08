#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80025850_arg0.h"


typedef struct S_800259CC_2 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800259CC_2;   /* ((Rec_func_80025850_arg0 *)arg0)->unk_18 in func_800259CC */




s32 func_80026C20();                    /* extern */


/* Check whether a type-4 context passes the linked object check. */
s32 func_800259CC(Rec_func_80025850_arg0 *context) {
    s32 check_passed;

    check_passed = 0;
    if (context->unk_08 == 4) {
        check_passed = func_80026C20(((S_800259CC_2 *)(((Rec_func_80025850_arg0 *)context)->unk_18))->unk_28, 0) == 0;
    }
    return check_passed;
}
