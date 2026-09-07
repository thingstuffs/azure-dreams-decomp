#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s16 func_800C8DB0();               /* extern */


u32 func_800C8788(Rec_D_800E3D7C *arg0, M2C_UNK arg1) {
    u8 temp_v0;

    temp_v0 = arg0->unk_10.at01_u8.v;
    return (u32) ~func_800C8DB0(arg1, temp_v0 * 4, (temp_v0 >> 2) + 0x10) >> 0x1F;
}
