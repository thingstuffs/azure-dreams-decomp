#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

s16 func_80095464();    /* extern */
u16 func_800BCB04();                   /* extern */



s16 func_80094ED4(s32 arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    s16 temp_v0;
    u16 temp_s2;

    temp_s2 = arg3->unk_88.as_u16;
    arg3->unk_88.as_u16 = func_800BCB04((arg2->unk_24 << 6) | 0x20, (arg2->unk_25 << 6) | 0x20, (s16) (temp_s2 - 0x20));
    temp_v0 = func_80095464(arg0, arg1, arg2, arg3);
    arg3->unk_88.as_u16 = temp_s2;
    return temp_v0;
}
