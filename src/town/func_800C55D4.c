/* cfail-repair: true-space rowbase definition */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_800C2CB0();
s32 func_800C2D0C();



void func_800C2D34(Rec_func_80094268_arg0 *arg0, Rec_D_80082E80 *arg1, s32 *arg2) {
    arg0->unk_78 = arg2;
    func_800C2CB0(arg0, arg1, arg0->unk_78[func_800C2D0C(arg0->unk_72.as_s16)], 0);
    arg1->unk_05.as_s8 = 0;
}
