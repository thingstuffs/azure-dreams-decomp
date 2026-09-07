#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033CD8();                   /* extern */
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800A7774[3];


void func_800A77D0(Rec_func_80094268_arg0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_90.as_u16 - 1;
    arg0->unk_90.as_u16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80033CD8(arg0, &D_80045340[0]);
        arg0->unk_90.as_u16 = 0xAU;
        arg0->unk_50.as_pm = &D_800A7774[0];
    }
}
