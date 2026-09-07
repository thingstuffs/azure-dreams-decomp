#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800374F4();                         /* extern */
extern M2C_UNK D_800A7950;


void func_800A790C(Rec_func_80094268_arg0 *arg0) {
    s16 temp_v0;

    arg0->unk_50.as_pm = &D_800A7950;
    temp_v0 = func_800374F4(0x60) + 0xC0;
    arg0->unk_90.as_s16 = temp_v0;
    arg0->unk_6C.as_s16 = temp_v0;
}
