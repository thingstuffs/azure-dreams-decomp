#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"


void func_80096AC0(Rec_func_8008ACDC_arg0 *arg0) {
    arg0->unk_9A.as_s8 = 0x34;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C.as_s32 = 0;
    arg0->unk_A2 = (u16) (arg0->unk_A2 & 0xFFFE);
}
